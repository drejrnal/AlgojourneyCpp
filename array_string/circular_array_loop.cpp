//
// Created by luoxiYun on 2021/8/7.
// lc457
//

#include "common.h"

bool findLoopInCircularArray( vector<int> &nums ){
    int n = nums.size();
    vector<int> next( n );
    for( int i = 0; i < n; i++ )
        next[i] = (i + nums[i]%n + n) % n; //括号里 +n 是考虑 i+nums[i]%n 为负数的情况
    for( int i = 0; i < n; i++ ) {
        int slow = i, fast = next[slow];
        //确保慢指针与快指针的移动是同一方向，并且快指针移动的两步也得保持方向一致
        while ( (nums[slow] * nums[fast] > 0) && ( nums[fast] * nums[next[fast]] > 0) ){
            if( slow == fast) {
                //确保循环长度大于1
                if( slow != next[slow] ){
                    return true;
                }
                break;
            }
            slow = next[slow];
            fast = next[next[fast]];
        }
    }
    return false;
};

int main(){
    vector<int> nums = { -2,1,-1,-2,-2 };
    cout<<findLoopInCircularArray(nums)<<endl;
    return 0;
}