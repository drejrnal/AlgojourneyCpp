#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// Class for managing large datasets that don't fit in memory
// Optimized version that works directly with memory-mapped files
class ExternalDataManagerOptimized {
private:
    const size_t DATA_TYPE_SIZE = sizeof(long long);
    const size_t CHUNK_SIZE = 1024 * 1024 * 128;  // 128MB chunks
    const size_t RECORDS_PER_CHUNK = CHUNK_SIZE / DATA_TYPE_SIZE;
    string base_filename;
    size_t total_elements;
    void *global_sorted_mapped;

    /*
     * Helper function to align an offset to the system page size
     * In mmap function, the offset must be aligned to the page size
     * otherwise it will return EINVAL error number
     */
    size_t alignToPageSize(size_t offset) {
        static const size_t pageSize = sysconf(_SC_PAGESIZE);
        // Use bit masking to align down to page boundary
        // Equivalent to: offset - (offset % pageSize)
        return offset & ~(pageSize - 1);
    }

    // Sort directly in the memory-mapped region
    void sortMappedChunk(void *mapped_data, size_t num_elements) {
        long long *data = static_cast<long long *>(mapped_data);
        std::sort(data, data + num_elements);
    }

    // Unmap a previously mapped region
    void unmapChunk(void *mapped, size_t length, int fd) {
        if (mapped != MAP_FAILED) {
            // Get page-aligned base address for unmapping
            static const size_t pageSize = sysconf(_SC_PAGESIZE);
            uintptr_t addr = reinterpret_cast<uintptr_t>(mapped);
            size_t misalignment = addr & (pageSize - 1);
            
            // If the pointer is misaligned, adjust it back to page boundary
            void *aligned_addr = mapped;
            size_t actual_length = length;

            if (misalignment > 0) {
                // Adjust pointer back to page boundary and increase length
                aligned_addr = reinterpret_cast<void*>(addr - misalignment);
                actual_length = length + misalignment;
            }
            
            // Ensure data is synchronized with disk
            msync(aligned_addr, actual_length, MS_SYNC);
            munmap(aligned_addr, actual_length);
        }
        if (fd != -1) {
            close(fd);
        }
    }

    // Create a sorted temp file by directly mapping and sorting chunks
    void createSortedTempFile(const string &input_file, const string &temp_file,
                              size_t start_element, size_t num_elements) {
        // Open or create the temp file
        int temp_fd = open(temp_file.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (temp_fd == -1) {
            cerr << "Failed to create temp file: " << temp_file << endl;
            return;
        }

        // Set the size of the temp file
        size_t temp_file_size = num_elements * DATA_TYPE_SIZE;
        if (ftruncate(temp_fd, temp_file_size) == -1) {
            cerr << "Failed to set temp file size" << endl;
            close(temp_fd);
            return;
        }

        // Map the entire temp file
        void *temp_mapped = mmap(NULL, temp_file_size, PROT_READ | PROT_WRITE,
                                 MAP_SHARED, temp_fd, 0);
        if (temp_mapped == MAP_FAILED) {
            cerr << "Failed to map temp file" << endl;
            close(temp_fd);
            return;
        }

        // Open the input file for reading
        int input_fd = open(input_file.c_str(), O_RDONLY);
        if (input_fd == -1) {
            cerr << "Failed to open input file: " << input_file << endl;
            unmapChunk(temp_mapped, temp_file_size, temp_fd);
            return;
        }

        // Map the relevant portion of the input file
        size_t input_offset = start_element * DATA_TYPE_SIZE;
        
        // Align offset to page size boundary
        size_t aligned_input_offset = alignToPageSize(input_offset);
        size_t offset_adjustment = input_offset - aligned_input_offset;
        size_t aligned_size = temp_file_size + offset_adjustment;
        
        void *input_mapped = mmap(NULL, aligned_size, PROT_READ, MAP_PRIVATE,
                                  input_fd, aligned_input_offset);
        if (input_mapped == MAP_FAILED) {
            cerr << "Failed to map input file: " << strerror(errno) << endl;
            close(input_fd);
            unmapChunk(temp_mapped, temp_file_size, temp_fd);
            return;
        }

        // Adjust the pointer to account for alignment
        char* aligned_ptr = static_cast<char*>(input_mapped);
        void* actual_start = aligned_ptr + offset_adjustment;
        
        // Copy data from input to temp file
        memcpy(temp_mapped, actual_start, temp_file_size);

        // Unmap input file
        munmap(input_mapped, aligned_size);
        close(input_fd);

        // Sort the data directly in the memory-mapped temp file
        sortMappedChunk(temp_mapped, num_elements);

        // Sync and unmap the temp file
        msync(temp_mapped, temp_file_size, MS_SYNC);
        munmap(temp_mapped, temp_file_size);
        close(temp_fd);
    }

    // Multi-way merge of sorted temporary files directly using memory mapping
    void multiWayMergeOptimized(const vector<string> &temp_files,
                                const string &output_file) {
        // Structure for priority queue
        struct ChunkItem {
            long long value;
            size_t file_index;
            size_t position;

            bool operator>(const ChunkItem &other) const {
                return value > other.value;
            }
        };

        // Open all temp files with memory mapping
        vector<pair<void *, int>> mapped_files;
        vector<size_t> file_sizes;

        for (const auto &file: temp_files) {
            int fd = open(file.c_str(), O_RDONLY);
            if (fd == -1) {
                cerr << "Failed to open temp file: " << file << endl;
                continue;
            }

            struct stat sb;
            if (fstat(fd, &sb) == -1) {
                cerr << "Failed to get file size for: " << file << endl;
                close(fd);
                continue;
            }

            // Use page-aligned memory mapping
            size_t filesize = sb.st_size;
            void *mapped = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
            if (mapped == MAP_FAILED) {
                cerr << "Failed to map temp file: " << file << ": " << strerror(errno) << endl;
                close(fd);
                continue;
            }

            mapped_files.push_back({mapped, fd});
            file_sizes.push_back(filesize / DATA_TYPE_SIZE);
        }

        // Create and map output file
        size_t total_output_elements = 0;
        for (size_t size: file_sizes) {
            total_output_elements += size;
        }

        int output_fd =
                open(output_file.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (output_fd == -1) {
            cerr << "Failed to create output file: " << output_file << endl;
            // Clean up mapped files
            for (int i = 0; i < mapped_files.size(); i++) {
                auto &[mapped, fd] = mapped_files[i];
                if (mapped != MAP_FAILED) {
                    munmap(mapped, file_sizes[i] * DATA_TYPE_SIZE);
                }
                if (fd != -1) {
                    close(fd);
                }
            }
            exit(-1);
        }

        // Set output file size
        size_t output_file_size = total_output_elements * DATA_TYPE_SIZE;
        if (ftruncate(output_fd, output_file_size) == -1) {
            cerr << "Failed to set output file size" << endl;
            close(output_fd);
            // Clean up mapped files
            for (int i = 0; i < mapped_files.size(); i++) {
                auto &[mapped, fd] = mapped_files[i];
                if (mapped != MAP_FAILED) {
                    munmap(mapped, file_sizes[i] * DATA_TYPE_SIZE);
                }
                if (fd != -1) {
                    close(fd);
                }
            }
            exit(-1);
        }

        // Initialize priority queue with first element from each file
        priority_queue<ChunkItem, vector<ChunkItem>, greater<ChunkItem>> pq;
        for (size_t i = 0; i < mapped_files.size(); i++) {
            if (mapped_files[i].first != MAP_FAILED && file_sizes[i] > 0) {
                long long *data =
                        static_cast<long long *>(mapped_files[i].first);
                pq.push({data[0], i, 0});
            }
        }
        void *output_mapped = mmap(NULL, output_file_size, PROT_READ | PROT_WRITE,
                                   MAP_SHARED, output_fd, 0);
        global_sorted_mapped = output_mapped;
        if (output_mapped == MAP_FAILED) {
            cerr << "Failed to map output file at offset "
                 <<" due to "<<strerror(errno)<< endl;

            close(output_fd);
            // Clean up mapped files
            for (int i = 0; i < mapped_files.size(); i++) {
                auto &[mapped, fd] = mapped_files[i];
                if (mapped != MAP_FAILED) {
                    munmap(mapped, file_sizes[i] * DATA_TYPE_SIZE);
                }
                if (fd != -1) {
                    close(fd);
                }
            }
            exit(-1);
        }
        size_t remaining_output_size = output_file_size;
        // Merge chunks
        while (!pq.empty() && remaining_output_size > 0) {
            // Map the next chunk of the output file
            long long *output_data = reinterpret_cast<long long *>(output_mapped);
            
            size_t output_elements_written = 0;
            size_t max_elements_in_chunk = CHUNK_SIZE / DATA_TYPE_SIZE;

            // Fill the current output chunk from the priority queue
            while (!pq.empty() &&
                   output_elements_written < max_elements_in_chunk) {
                ChunkItem current = pq.top();
                pq.pop();

                // Write the smallest value to the output
                output_data[output_elements_written++] = current.value;

                // Move to the next element in the input file
                if (current.position + 1 < file_sizes[current.file_index]) {
                    long long *data = static_cast<long long *>(
                            mapped_files[current.file_index].first);
                    pq.push({data[current.position + 1], current.file_index,
                             current.position + 1});
                }
            }

            // Synchronize and unmap the output chunk
            msync(output_mapped, CHUNK_SIZE, MS_SYNC);

            // Update offsets and remaining size
            remaining_output_size -= output_elements_written * DATA_TYPE_SIZE;
            output_mapped = static_cast<char *>(output_mapped) +
                            output_elements_written * DATA_TYPE_SIZE;
        }

        close(output_fd);

        // Clean up mapped files
        for (size_t i = 0; i < mapped_files.size(); i++) {
            if (mapped_files[i].first != MAP_FAILED) {
                munmap(mapped_files[i].first, file_sizes[i] * DATA_TYPE_SIZE);
            }
            if (mapped_files[i].second != -1) {
                close(mapped_files[i].second);
            }
        }
    }

public:
    ExternalDataManagerOptimized(const string &filename, size_t num_elements)
            : base_filename(filename), total_elements(num_elements) {}
    ~ExternalDataManagerOptimized() {
        // Clean up any remaining mapped regions
        if (global_sorted_mapped != nullptr && global_sorted_mapped != MAP_FAILED) {
            cout << "Cleaning up global sorted mapped region..." << endl;
            munmap(global_sorted_mapped, total_elements * DATA_TYPE_SIZE);
        }
    }

    // Create a large dataset with random values for testing
    void generateTestData() {
        cout << "Generating test data..." << endl;
        string filename = base_filename + "_data.bin";

        // Use memory mapping for large file creation
        size_t total_size = total_elements * DATA_TYPE_SIZE;

        // Create file and set its size
        int fd = open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (fd == -1) {
            cerr << "Failed to create data file" << endl;
            return;
        }

        // Extend file to required size
        if (ftruncate(fd, total_size) == -1) {
            cerr << "Failed to set file size" << endl;
            close(fd);
            return;
        }

        // Use chunked memory mapping for very large files
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<long long> dist(0, 6666666);

        for (size_t offset = 0; offset < total_size; offset += CHUNK_SIZE) {
            size_t current_chunk_size = min(CHUNK_SIZE, total_size - offset);
            size_t current_elements = current_chunk_size / DATA_TYPE_SIZE;

            // Map chunk
            void *mapped = mmap(NULL, current_chunk_size, PROT_WRITE,
                                MAP_SHARED, fd, offset);
            if (mapped == MAP_FAILED) {
                cerr << "Failed to mmap for writing at offset " << offset
                     << endl;
                close(fd);
                return;
            }

            // Generate random values directly into mapped memory
            long long *data_ptr = static_cast<long long *>(mapped);
            for (size_t i = 0; i < current_elements; i++) {
                data_ptr[i] = dist(gen);
            }

            // Flush to disk
            msync(mapped, current_chunk_size, MS_SYNC);
            munmap(mapped, current_chunk_size);

            cout << "Generated " << (offset / DATA_TYPE_SIZE + current_elements)
                 << " / " << total_elements << " elements" << endl;
        }

        close(fd);
        cout << "Test data generation complete" << endl;
    }

    // Sort the large dataset using optimized external sorting with memory
    // mapping
    void sortData() {
        cout
                << "Starting optimized external sort using direct memory mapping..."
                << endl;
        auto start_time = chrono::high_resolution_clock::now();

        string input_file = base_filename + "_data.bin";
        vector<string> temp_files;

        // Phase 1: Create sorted temporary files
        size_t elements_processed = 0;
        size_t chunk_id = 0;

        cout << "Phase 1: Creating sorted temporary files..." << endl;

        // For larger datasets, this can be parallelized
        vector<thread> sorting_threads;
        const size_t MAX_CONCURRENT_THREADS = thread::hardware_concurrency();

        while (elements_processed < total_elements) {
            size_t elements_to_process =
                    min(RECORDS_PER_CHUNK, total_elements - elements_processed);

            string temp_file =
                    base_filename + "_temp_" + to_string(chunk_id) + ".bin";
            temp_files.push_back(temp_file);

            // If we have enough threads, wait for one to finish
            if (sorting_threads.size() >= MAX_CONCURRENT_THREADS) {
                for (auto &thread: sorting_threads) {
                    if (thread.joinable()) {
                        thread.join();
                    }
                }
                sorting_threads.clear();
            }

            // Create and sort a temp file in a separate thread
            sorting_threads.emplace_back([this, input_file, temp_file,
                                                 elements_processed,
                                                 elements_to_process]() {
                this->createSortedTempFile(input_file, temp_file,
                                           elements_processed,
                                           elements_to_process);
            });

            elements_processed += elements_to_process;
            chunk_id++;

            cout << "Scheduled chunk " << chunk_id << " (" << elements_processed
                 << "/" << total_elements << " elements)" << endl;
        }

        // Wait for all sorting threads to complete
        for (auto &thread: sorting_threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        // Phase 2: Merge sorted temp files
        cout << "Phase 2: Merging " << temp_files.size()
             << " sorted temporary files..." << endl;
        string output_file = base_filename + "_sorted.bin";
        multiWayMergeOptimized(temp_files, output_file);

        // Calculate time taken
        auto end_time = chrono::high_resolution_clock::now();
        auto duration =
                chrono::duration_cast<chrono::seconds>(end_time - start_time)
                        .count();
        cout << "External sort completed in " << duration << " seconds" << endl;

        // Clean up temp files
        for (const auto &file: temp_files) {
            remove(file.c_str());
        }
    }

    // Read a range of values from the sorted file
    vector<long long> readRange(size_t start, size_t count) {
        // Copy data to vector for return
        long long *data = static_cast<long long *>(global_sorted_mapped);
        vector<long long> result(data + start,
                                  data + min(start + count, total_elements));
        return result;
    }

    // Search for values using binary search - more efficient implementation
    pair<size_t , size_t > searchValue(long long target) {
        string sorted_file = base_filename + "_sorted.bin";
        vector<size_t> positions;

        // We'll use a modified binary search that maps chunks on demand
        size_t left = 0;
        size_t right = total_elements - 1;

        long long *data = static_cast<long long *>(global_sorted_mapped);

        //find the lower boundary of position equal to target
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            long long mid_value = data[mid];
            if (mid_value < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        size_t lower_boundary = data[right] == target ? right : -1;
        //find the upper boundary of position equal to target
        left = 0;
        right = total_elements - 1;
        while(left < right) {
            size_t mid = left + (right - left) / 2;
            long long mid_value = data[mid];
            if (mid_value <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        size_t right_boundary = data[right] == target ? right : (data[right-1] == target ? right - 1 : -1);

        return {lower_boundary, right_boundary};
    }
};

int main() {
    // Small test for demonstration
    // In reality this would handle billions of elements
    const size_t TEST_SIZE = 100000000;  // 1 million elements for testing

    ExternalDataManagerOptimized manager("large_data_opt", TEST_SIZE);

    int choice;
    cout << "Optimized External Data Manager Menu:" << endl;
    cout << "1. Generate test data" << endl;
    cout << "2. Sort data (external sort with in-memory mapped chunks)" << endl;
    cout << "3. Read range" << endl;
    cout << "4. Search value" << endl;
    cout << "0. Exit" << endl;

    do {
        cout << "> ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.generateTestData();
                break;
            case 2:
                manager.sortData();
                break;
            case 3: {
                size_t start, count;
                cout << "Enter start position: ";
                cin >> start;
                cout << "Enter count: ";
                cin >> count;

                vector<long long> values = manager.readRange(start, count);
                cout << "Read " << values.size() << " values:" << endl;
                for (size_t i = 0; i < min(size_t(10), values.size()); i++) {
                    cout << values[i] << " ";
                }
                if (values.size() > 10) cout << "...";
                cout << endl;
                break;
            }
            case 4: {
                long long value;
                cout << "Enter value to search: ";
                cin >> value;

                auto positions = manager.searchValue(value);
                cout << "Position of value " << value << ": "
                     << "Lower boundary: " << positions.first
                     << ", Upper boundary: " << positions.second << endl;
                cout << endl;
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}