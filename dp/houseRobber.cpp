//
// Created by luoxiYun on 2021/3/24.
//

#include "common.h"

class HouseRobber{

public:
    int robberValue( vector<int> &nums, int begin, int end ){
        vector<int> dp( end - begin + 1 , 0 );
        dp[0] = nums[0]; dp[1] = max( nums[0], nums[1] );
        for( int i = 2; i <= end; i++ ){
            dp[i] = max( dp[i-2] + nums[i], dp[i-1] );
        }
        return dp[end];
    }
    //空间压缩后的动态规划写法
    int robborValueCompact( vector<int> &nums, int begin, int end ){
        int dp_i_2 = nums[begin];
        int dp_i_1 = max( nums[begin], nums[begin+1] );
        int len = end - begin + 1;
        if( len == 1)
            return dp_i_2;
        if( len ==2 )
            return dp_i_1;

        int dp_i = 0;
        for( int i = begin+2; i <= end; i++ ){
            int tmp = dp_i_1;
            dp_i = max( dp_i_1, dp_i_2+nums[i] );
            dp_i_1 = dp_i;
            dp_i_2 = tmp;
        }
        return dp_i;
    }

    int robborValueRing( vector<int> &nums ){
        int res1 = robborValueCompact( nums, 0, nums.size() - 2 );
        int res2 = robborValueCompact( nums, 1, nums.size() - 1 );
        return max( res1, res2 );
    }

};

int main(){
    HouseRobber houseRobber;
    vector<int> num = { 2,3,1 };
    cout<<houseRobber.robborValueRing( num )<<endl;
    return 0;
}