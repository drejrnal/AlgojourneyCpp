#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
class LongestConsectiveSequence {
public:
	int longestConsecutive(vector<int> &nums) {
		unordered_set<int> numSet(nums.begin(), nums.end());
		int longest = 0;
		for (int num : numSet) {
			if (numSet.find(num - 1) == numSet.end()) {
				int currentNum = num;
				int currentLen = 1;
				while (numSet.find(currentNum + 1) != numSet.end()) {
					currentNum += 1;
					currentLen += 1;
				}
				longest = max(currentLen, longest);
			}
		}
		return longest;
	}
};

int main() {
	LongestConsectiveSequence longestConsectiveSequence;
	vector<int> nums = {100, 4, 200, 1, 3, 2};
	cout << longestConsectiveSequence.longestConsecutive(nums) << endl;
	return 0;
}