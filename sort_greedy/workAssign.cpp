//
// Created by luoxiYun on 2021/3/23.
//

#include "common.h"

class maxProfitScheme {
public:
	//复杂度较高
	/*int maxProfitAssignment( vector<int> &difficulty, vector<int> &profit,
	vector<int> workers ){ vector<pair<int, int>> num;

	    for( int i = 0; i < difficulty.size(); i++ )
	        num.push_back( { difficulty[i], profit[i] } );

	    sort( num.begin(), num.end(),
	          []( const pair<int, int> &left, const pair<int, int> &right){
	              return left.first < right.first;
	          }
	    );

	    int sum = 0;
	    for( int capacity : workers ){
	        auto it = upper_bound( num.begin(), num.end(), capacity,
	                               [](int target, const pair<int, int> &right){
	            return target < right.first;
	        } );

	        if( it == num.begin() && it->first > capacity )
	            continue;

	        if( it == num.end() || it->first > capacity)
	            it = prev(it);

	        int profit = it->second;
	        for( auto iter = num.begin(); iter <= it; iter++ )
	            if( iter->second > profit )
	                profit = iter->second;
	        sum +=profit;
	    }
	    return sum;
	}*/

	//双指针 一趟遍历降低复杂度
	int maxProfitAssignment(vector<int> &difficulty, vector<int> &profit,
	                        vector<int> &worker) {
		vector<pair<int, int>> num;

		for (int i = 0; i < difficulty.size(); i++)
			num.push_back({difficulty[i], profit[i]});

		sort(num.begin(), num.end(),
		     [](const pair<int, int> &left, const pair<int, int> &right) {
			     return left.first < right.first;
		     });

		sort(worker.begin(), worker.end());
		int workerPtr = 0, numPtr = 0;
		int bonus = -1;
		int res = 0;
		while (workerPtr < worker.size()) {
			while (numPtr < num.size() &&
			       worker[workerPtr] >= num[numPtr].first) {
				bonus = max(bonus, num[numPtr].second);
				numPtr++;
			}
			if (bonus != -1) res += bonus;
			workerPtr++;
		}
		return res;
	}
};

int main() {
	maxProfitScheme mps;
	vector<int> difficulty = {68, 35, 52, 47, 86};
	vector<int> profit = {67, 17, 1, 81, 3};
	vector<int> workers = {92, 10, 85, 84, 82};
	cout << mps.maxProfitAssignment(difficulty, profit, workers) << endl;
	return 0;
}