//
// Created by luoxiYun on 2021/7/3.
// 当前目录下的backPack.cpp 主要是dp问题中的经典背包问题，那里用背包问题的思路解决过coin change问题
// 但是 上述文件内的代码过于程式化，套路化，是过分依赖算法套路文章中介绍背包解题思路的产物，更像是死记硬背思路
// 笔者近期思考了如何入手这类dp问题，怎么进行阶段划分、每个阶段又如何进行状态划分、前后阶段间的依赖关系如何建立
// 通过这种正规的解题思路重新认识以往解决过的dp问题
//
class coin_cat {

    int change(int amount, vector<int>& coins) {
        if( coins.size() == 0 )
            return 0;
        int m = coins.size();
        vector<vector<int>> dp(m, vector<int>(amount+1, 0));
        dp[0][0] = 1;
        for( int i = coins[0]; i <= amount; i+=coins[0] )
            dp[0][i] = 1;

        for( int i = 1; i < dp.size(); i++ ){
            for( int j = 0; j <= amount; j++ ){
                dp[i][j] = dp[i-1][j];
                if( j - coins[i] >= 0 )
                    dp[i][j] +=dp[i][j - coins[i]];
            }
        }
        return dp[m-1][amount];
    }

};