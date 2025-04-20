//
// Coding Test Solution: Remove duplicates from an array
//

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
	// Solution will be implemented here based on the problem description
	vector<int> removeDuplicatesConcise(const vector<int>& nums) {
		// Create unordered_set from vector - automatically removes duplicates
		unordered_set<int> unique_set(nums.begin(), nums.end());

		// Convert set back to vector
		return vector<int>(unique_set.begin(), unique_set.end());
	}
};

int main() {
	Solution solution;

	// Read input
	int n;
	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	// Remove duplicates using the concise method
	vector<int> result = solution.removeDuplicatesConcise(nums);

	// Output the result
	for (int num : result) {
		cout << num << " ";
	}
	cout << endl;

	return 0;
}
