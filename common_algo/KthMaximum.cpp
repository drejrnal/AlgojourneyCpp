//
// Created by luoxiYun on 2021/3/11.
//

#include <cstdlib>
#include <ctime>

#include "common.h"

class kthMaximum {
public:
    // Quicksort implementation
    void quickSort(vector<int> &nums, int l, int r) {
        if (l < r) {
            int pivotIndex = randomPartition(nums, l, r);
            quickSort(nums, l, pivotIndex - 1);
            quickSort(nums, pivotIndex + 1, r);
        }
    }

    // Sort the entire array
    void sort(vector<int> &nums) {
        srand(time(0));
        quickSort(nums, 0, nums.size() - 1);
    }

    int randomPartition(vector<int> &nums, int l, int r) {
        int pos = rand() % (r - l + 1) + l;
        /*
         * 此处如果swap的参数是const的，则函数编译出错
         */
        std::swap(nums[pos], nums[r]);
        return partition(nums, l, r);
    }

    int partition(vector<int> &nums, int l, int r) {
        int left = l - 1;
        int pivot = nums[r];
        for (int i = l; i < r; i++) {
            if (nums[i] <= pivot) {
                std::swap(nums[++left], nums[i]);
            }
        }
        std::swap(nums[left + 1], nums[r]);
        // nums[l...left+1] <= x < nums[left+2...r]
        return left + 1;
    }

    int quickSelect(vector<int> &nums, int l, int r, int k) {
        int pos = randomPartition(nums, l, r);
        if (pos == k)
            return nums[pos];
        else if (pos < k)
            return quickSelect(nums, pos + 1, r, k);
        else
            return quickSelect(nums, l, pos - 1, k);
    }

    int findKth(vector<int> &nums, int k) {
        srand(time(0));
        int l = 0, r = nums.size() - 1;
        return quickSelect(nums, l, r, nums.size() - k);
    }
};

/*
 * Complexity Analysis - QuickSort vs QuickSelect
 *
 * QuickSort - O(nlogn) Average Time Complexity:
 * 1. Each partition operation takes O(n) time
 * 2. In the average case, the pivot divides the array into roughly equal halves
 * 3. We recursively sort BOTH halves after each partition
 * 4. This creates a recurrence relation: T(n) = 2T(n/2) + O(n)
 * 5. This solves to O(nlogn) using the master theorem
 *
 * QuickSelect - O(n) Average Time Complexity:
 * 1. Each partition operation still takes O(n) time
 * 2. However, after partitioning, we only recurse on ONE half of the array
 * 3. The recurrence relation becomes: T(n) = T(n/2) + O(n)
 * 4. This solves to O(n) using the master theorem
 *
 * The key difference is that QuickSelect only explores one branch of the
 * recursion tree, while QuickSort must explore both branches.
 *
 * Visually:
 * QuickSort recursion tree:       QuickSelect recursion tree:
 *         n                                n
 *       /   \                             /
 *     n/2   n/2                         n/2
 *    /  \   /  \                        /
 *  n/4 n/4 n/4 n/4                    n/4
 *  ...  ... ... ...                    ...
 *
 * This is why QuickSelect has O(n) complexity while QuickSort has O(nlogn).
 */

int main() {
    kthMaximum kmm;

    // Test quickSelect (find kth largest)
    vector<int> nums1 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k = 3;
    cout << "The " << k << "rd largest element is: " << kmm.findKth(nums1, k)
         << endl;

    // Test quickSort
    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << "Array before sorting: ";
    for (int num: nums2) cout << num << " ";
    cout << endl;

    kmm.sort(nums2);

    cout << "Array after sorting: ";
    for (int num: nums2) cout << num << " ";
    cout << endl;

    return 0;
}