#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

// Simple test to verify that sorting data in a memory-mapped region
// directly reflects changes in the underlying file without explicit writes
void test_mmap_sort_reflection() {
    const string filename = "mmap_sort_test.bin";
    const size_t num_elements = 100;  // Small number for easy verification
    const size_t data_size = num_elements * sizeof(int);

    // Step 1: Create a file with random integers
    cout << "Step 1: Creating test file with random integers..." << endl;

    // Create and open the file
    int fd = open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        cerr << "Failed to create test file" << endl;
        return;
    }

    // Set file size
    if (ftruncate(fd, data_size) == -1) {
        cerr << "Failed to set file size" << endl;
        close(fd);
        return;
    }

    // Generate random integers
    vector<int> original_data(num_elements);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000);

    for (size_t i = 0; i < num_elements; i++) {
        original_data[i] = dist(gen);
    }

    // Map the file for writing the initial data
    void *mapped = mmap(NULL, data_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        cerr << "Failed to map file for initial write" << endl;
        close(fd);
        return;
    }

    // Write random data to the mapped region
    memcpy(mapped, original_data.data(), data_size);

    // Ensure data is synced to disk
    msync(mapped, data_size, MS_SYNC);

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        cerr << "Failed to get file size" << endl;
        return;
    }
    cout << "File size: " << sb.st_size << " bytes "
         << ((sb.st_size == data_size) ? "Equal data_size"
                                       : "Not equal data_size")
         << endl;

    // Unmap the file
    munmap(mapped, data_size);
    close(fd);

    // Step 2: Re-open the file, map it, and sort the data in-place
    cout << "\nStep 2: Sorting data directly in the memory-mapped region..."
         << endl;

    fd = open(filename.c_str(), O_RDWR);
    if (fd == -1) {
        cerr << "Failed to open file for sorting" << endl;
        return;
    }

    // Map the file for reading and writing
    mapped = mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        cerr << "Failed to map file for sorting" << endl;
        close(fd);
        return;
    }

    // Sort the data directly in the mapped memory
    int *mapped_ints = static_cast<int *>(mapped);
    std::sort(mapped_ints, mapped_ints + num_elements);

    // Sync changes to disk
    msync(mapped, data_size, MS_SYNC);

    // Create a sorted copy of the original data for comparison
    vector<int> expected_sorted_data = original_data;
    std::sort(expected_sorted_data.begin(), expected_sorted_data.end());

    // Print first 10 elements of the sorted data in memory
    cout << "Sorted data in memory (first 10 elements):" << endl;
    for (size_t i = 0; i < min(size_t(10), num_elements); i++) {
        cout << mapped_ints[i] << " ";
    }
    cout << endl;

    // Unmap and close
    munmap(mapped, data_size);
    close(fd);

    // Step 3: Re-open the file and verify that the sorting was reflected in the
    // file
    cout << "\nStep 3: Verifying that sorting was reflected in the file..."
         << endl;

    fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        cerr << "Failed to open file for final verification" << endl;
        return;
    }

    // Map the file for reading
    mapped = mmap(NULL, data_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        cerr << "Failed to map file for final verification" << endl;
        close(fd);
        return;
    }

    // Read the data from the file
    vector<int> final_verification_data(num_elements);
    memcpy(final_verification_data.data(), mapped, data_size);

    // Print first 10 elements from the file after sorting
    cout << "Data read from file after sorting (first 10 elements):" << endl;
    for (size_t i = 0; i < min(size_t(10), num_elements); i++) {
        cout << final_verification_data[i] << " ";
    }
    cout << endl;

    // Verify data is sorted and matches the expected sorted data
    bool final_verification_match =
            memcmp(expected_sorted_data.data(), final_verification_data.data(),
                   data_size) == 0;
    cout << "Final verification "
         << (final_verification_match ? "PASSED" : "FAILED") << endl;

    // Check if the array is actually sorted
    bool is_sorted = std::is_sorted(final_verification_data.begin(),
                                    final_verification_data.end());
    cout << "Is the file data sorted? " << (is_sorted ? "YES" : "NO") << endl;

    // Unmap and close
    munmap(mapped, data_size);
    close(fd);

    cout << "\nTest "
         << (final_verification_match && is_sorted ? "PASSED" : "FAILED") << "!"
         << endl;
    cout << "Changes made to the memory-mapped region "
         << (final_verification_match ? "WERE" : "WERE NOT")
         << " reflected in the file without explicit write operations." << endl;

    // Clean up the test file
    unlink(filename.c_str());
}

int main() {
    cout << "=== Memory-Mapped Sort Reflection Test ===" << endl;
    test_mmap_sort_reflection();
    return 0;
}