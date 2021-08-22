//
// Created by luoxiYun on 2021/8/18.
//

#include "common.h"
/*
 * 给定长度为N的整数数组，以及M个互不相同的整数，请找出包含这M个整数的最短子数组。
例如：给定数组[4 2 1 3]，包含数字集{2, 3}的最短子数组是[2 1 3]，包含数字集{1, 3}的最短子数组是[1 3]。
 *与 leetcode 76题目类似
 */
int find_minimum_subarray_containing( vector<int> &origin, unordered_set<int> &candidates ){
    unordered_map<int, int> candidates_to_frequency;
    int left = 0, right = 0;
    int res = INT32_MAX;
    while ( right < origin.size() ){
        while ( candidates.find(origin[left]) == candidates.end() ) {
            left++;
        }
        while ( right < origin.size() && candidates_to_frequency.size() < candidates.size() ){
            if( candidates.find(origin[right]) != candidates.end() ){
                candidates_to_frequency[origin[right]] +=1;
            }
            right++;
        }
        if( right <= origin.size() && candidates_to_frequency.size() == candidates.size() ){
            while ( candidates.find(origin[left]) == candidates.end() || candidates_to_frequency[origin[left]] > 1 ){
                if( candidates.find(origin[left]) != candidates.end() )
                    candidates_to_frequency[origin[left]] -=1;
                left++;
            }
            res = min( res, right - left );
            candidates_to_frequency[origin[left]] -=1;
            candidates_to_frequency.erase(origin[left]);
            left++;
        }
    }
    return res == INT32_MAX ? 0 : res;
}

int main(){
    int examples;
    cin>>examples;
    int N, M;
    int num;
    vector<int> arrs;
    unordered_set<int> candidates;
    while ( examples-- ) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> num;
            arrs.push_back(num);
        }
        cin >> M;
        for (int i = 0; i < M; i++) {
            cin >> num;
            candidates.insert(num);
        }

        cout << find_minimum_subarray_containing(arrs, candidates) << endl;
        arrs.clear();
        candidates.clear();
    }
    return 0;
}