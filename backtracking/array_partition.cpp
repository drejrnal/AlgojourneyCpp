//
// Created by luoxiYun on 2021/9/10.
//
/*
 * 【数组分组】
 * 输入int型数组，询问该数组能否分成两组，使得两组中各元素加起来的和相等，
 * 数组值可正可负
 * 并且，所有5的倍数必须在其中一个组中，所有3的倍数在另一个组中（不包括5的倍数）
 * 满足以上条件，输出true；不满足时输出false。
 *
 * 注意此题一开始以背包问题思路求解（类似目标和问题解法），那种方法可适用于所有数均为正数的情形。
 */
#include "common.h"

typedef long long ll;

bool dfs( vector<int> &nums, int begin, vector<int> &partition,  ll target ) {
    if (begin == nums.size()) {
        ll partial_sum = accumulate( partition.begin(), partition.end(), 0 );
        if( partial_sum == target )
            return true;
        return false;
    }
    bool three_dividable = (nums[begin] % 3 == 0), five_dividable = (nums[begin] % 5 == 0);
    bool res;
    //如果是5的倍数，partiton一定包含nums[begin]
    if( five_dividable ){
        partition.push_back( nums[begin] );
        res = dfs( nums, begin+1, partition, target );
        if( res )
            return true;
        partition.pop_back();
    }else{
        if( !three_dividable ){
            partition.push_back( nums[begin] );
            res = dfs( nums, begin+1, partition, target );
            if( res )
                return true;
            partition.pop_back();
        }
        //partiton不包含nums[begin](是3的倍数，或者不是3的倍数)
        res = dfs( nums, begin+1, partition, target );
        if( res )
            return true;
    }
    return false;
}

bool can_partition( vector<int> &nums ){
    ll summation = accumulate( nums.begin(), nums.end(), 0 );
    if( summation & 1 )
        return false;
    vector<int> partial;
    return dfs( nums, 0, partial, summation/2 );
}

int main(){
    int n;
    while(cin>>n){
        vector<int> arr(n);
        for( int i = 0; i < n; i++ )
            cin>>arr[i];
        bool res = can_partition(arr);
        cout<<(res ? "true" : "false")<<endl;
    }
    return 0;
}