//
// Created by luoxiYun on 2021/3/12.
//

#include "common.h"


class backPack{
    const int NUM_MAX = 1e9+7;
public:

    int backPack01( vector<int> weights, vector<int> &values, int capacity ){
        vector<int> dp( capacity + 1, 0 );
        for( int i = 0; i < weights.size(); i++ ){
            for( int j = capacity; j > 0; j-- ){
                if( j >= weights[i] ){
                    dp[j] = max( dp[j], dp[j - weights[i]] + values[i]);
                }
            }
        }
        return dp[capacity];
    }

    /*  三维0-1背包问题
     *  力扣 879 盈利计划
     */
    int profitScheme( vector<int> &groups, vector<int> &profit, int n, int minProfit ){
        //初始化dp数组
        vector<vector<vector<int>>> dp( profit.size()+1, vector<vector<int>>(n+1,
                vector<int>(minProfit+1, 0)));

        for( int i = 1; i < dp.size(); i++ ){
            for( int j = 1; j <= n; j++ ){
                for( int k = 0; k <= minProfit; k++){
                    int addition = 0;
                    if( j - groups[i-1] >= 0 ){
                        if( k - profit[i-1] > 0 )
                            addition = dp[i-1][j - groups[i-1]][k-profit[i-1]];
                        else
                            addition = dp[i-1][j-groups[i-1]][0] + 1;
                    }
                    dp[i][j][k] = (addition + dp[i-1][j][k]) % NUM_MAX;
                }
            }
        }
        //考虑最小利润为0时，一个计划也不参与的情况
        if( minProfit == 0 )
            dp[profit.size()][n][minProfit] +=1;
        return dp[profit.size()][n][minProfit];
    }


    int backPackComplete( vector<int> &weights,vector<int> &vals, int capacity ){
        vector<int> dp( capacity+1, 0X3f3f3f3f );
        dp[0] = 0;
        for ( int i = 0; i < weights.size(); i++ ) {
            for ( int j = 0; j <= capacity; j++ ) {
                if (j >= weights[i]) {
                    dp[j] = min( dp[j], dp[j - weights[i]] + vals[i] );
                }
            }
         }
        return dp[capacity] < 0x3f3f3f3f ? dp[capacity] : -1;
    }

    int coinChange( vector<int> &coins, int target ){
        vector<int> vals( coins.size(), 1 );
        return backPackComplete( coins, vals, target );
    }

    /*
     * 力扣 题目416 partition equal subset sum
     * 前提：数组内元素均为正数
     */
    bool partitionIntoEqual( vector<int> &nums ){
        int sum = accumulate( nums.begin(), nums.end(), 0 );
        if ( sum & 1 )
            return false;
        else {
            return backPack01(nums, nums, sum / 2) == sum / 2;
        }
    }

    /*
     * 石头碰撞问题
     * 给定一组石头，每个石头有一个正数的重量。每一轮开始的时候，选择两个石头一起碰撞，
     * 假定两个石头的重量为x，y，x<=y,碰撞结果为
     * 1. 如果x==y，碰撞结果为两个石头消失
     * 2. 如果x != y，碰撞结果两个石头消失，生成一个新的石头，新石头重量为y-x
     * 最终最多剩下一个石头为结束。求解最小的剩余石头质量的可能性是多少。
     *
     * 思路：
     * 将数组分成两部分，记为A和B，使 | A - B |值尽可能小
     * 数组分开后，尽可能使其中一半的和往sum/2靠
     */
    int partition_array( vector<int> stones ){
        int sum = accumulate( stones.begin(), stones.end(), 0 );
        vector<int> dp( sum/2 + 1);
        for( int i = 0; i < stones.size(); i++ ) {
            for (int j = sum / 2; j >= 0; j--) {
                if ( j >= stones[i] )
                    dp[j] = max( dp[j], dp[j - stones[i]] + stones[i] );
            }
        }
        int other = sum - dp[sum/2];
        return other - dp[sum/2];
    }

};


int main(){
    /*vector<int> profit = { 6,7,8 };
    vector<int> group = { 2,3,5 };
    int n = 10;
    int target = 5;
    backPack backPack01;
    //cout<<backPack01.partitionIntoEqual(nums);
    cout<<backPack01.profitScheme( group, profit, n, target )<<endl;*/
    int num;
    cin>>num;
    backPack backPack01;
    vector<int> stones;
    for( int i = 0; i < num; i++ ) {
        int stone;
        cin >> stone;
        stones.push_back(stone);
    }
    cout<<backPack01.partition_array( stones )<<endl;
    return 0;
}

