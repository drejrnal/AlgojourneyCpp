//
// Created by luoxiYun on 2021/3/21.
//

#include "common.h"

// longest increasing subsequence

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
};

int main(){
    vector<int> input = { 2,1,5,3,6,4,8,9,7 };
    LIS lis;
    lis.longestIncreasingSubsequence(input);
    return 0;
}