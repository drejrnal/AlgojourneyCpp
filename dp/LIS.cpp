//
// Created by luoxiYun on 2021/3/21.
//

#include "common.h"

/* longest increasing subsequence
 * 最长非递减序列系列问题
 */
class LIS{

public:
    vector<int> longestIncreasingSubsequence( vector<int> &sequence ){
        int size = sequence.size();
        vector<int> result;
        int lis[size+1], dp[size];
        memset( lis, 0x3f, sizeof(lis) );
        lis[0] = -1;
        lis[1] = sequence[0];
        dp[0] = 1;
        for( int i = 1; i < size; i++ ) {
            int low = 1, high = i + 1;
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (sequence[i] > lis[mid])
                    low = mid + 1;
                else if (sequence[i] == lis[mid])
                    low = mid + 1;
                else
                    high = mid;
            }
            dp[i] = low;
            lis[low] = min( lis[low], sequence[i] );
        }

        for( int i = 1; i < size+1; i++ )
            if( lis[i] < 0x3f3f3f3f )
                cout<<lis[i]<<" ";
        cout<<endl;
        int lisn = *max_element(dp, dp + size );
        int trav = lisn;
        for( int i = sequence.size()-1; i >= 0; i-- ){
            if( dp[i] == trav ) {
                result.push_back(sequence[i]);
                trav--;
            }
        }

        reverse( result.begin(), result.end() );
        for( int ele : result )
            cout<<ele<<" ";
        cout<<endl;
        return result;
    }
    /*
     * 力扣(1964): find the longest obstacle course at each position
     */
    vector<int> longestObstacleCourse( vector<int> &obstacles ){
        int max_length = obstacles.size();
        //min_at_length[i]的含义表示 长度为i的非递减序列中，序列最后一个元素最小值
        vector<int> min_at_length( max_length+1, INT32_MAX );
        vector<int> dp( max_length, 0 );
        min_at_length[0] = 0;
        min_at_length[1] = obstacles[0];
        dp[0] = 1;
        for( int i = 1; i < max_length; i++ ){
            auto iter = upper_bound(min_at_length.begin(), min_at_length.end(), obstacles[i]);
            *iter = min( *iter, obstacles[i] );
            dp[i] = distance(min_at_length.begin(), iter);
        }
        for( int ele : min_at_length )
            cout<<ele<<" ";
        cout<<endl;
        return dp;
    }
};

int main(){
    vector<int> input = { 0,1,2,3,4,4,8,9,9 };
    LIS lis;
    //lis.longestIncreasingSubsequence(input);
    vector<int> res = lis.longestObstacleCourse( input );
    for( int ele : res )
        cout<<ele<<" ";
    cout<<endl;
    return 0;
}