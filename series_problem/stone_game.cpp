//
// Created by luoxiYun on 2021/8/21.
//

#include "common.h"

/*
 * alice(先手)和bob轮流从最左端和最右端取石子，最终拥有石子数最多的选手获胜
 * 返回两选手尽全力后，各自最大的得分数。
 */
int stone_game_minimum_diff( vector<int> &stones ){
    using Pair = pair<int, int>;
    int n = stones.size();
    vector< vector<Pair> > dp( stones.size(), vector<Pair>( n ) );
    for( int i = 0; i < n; i++ ){
        dp[i][i].first = stones[i];
        dp[i][i].second = 0;
    }
    for( int len = 1; len < n; len++ ){
        for( int begin = 0; begin + len < n; begin++ ){
            int left = stones[begin] + dp[begin+1][begin+len].second;
            int right = stones[begin+len] + dp[begin][begin+len-1].second;
            dp[begin][begin+len].first = max( left, right );
            dp[begin][begin+len].second = left > right ? (dp[begin+1][begin+len].first) : (dp[begin][begin+len-1].first) ;
        }
    }
    //dp[0][n-1].first表示Alice可获得的最大石头数，dp[0][n-1].second表示Bob可获得的最大石头数
    return dp[0][n-1].first - dp[0][n-1].second;
}

/*
 * alice(先手)和bob轮流从最左端和最右端取石子，最终拥有石子数最多的选手获胜
 * 返回score(alice) - score(bob)的最大值,本题与《算法实战》P239 9.17数字游戏类似
 * dp[i][j]含义：获取区间[i..j]上的石子时，（当前取石头的选手 - 另一位选手）石头收益差值的最大值
 */
int stone_game_maximum_diff( vector<int> &stones ){
    int n = stones.size();
    vector<vector<int>> dp( n, vector<int>(n, 0));
    vector<int> presum( n+1, 0 );
    for( int i = 1; i <= n; i++ )
        presum[i] = presum[i-1] + stones[i-1];
    for( int i = 0; i < n-1; i++ )
        dp[i][i+1] = max( stones[i], stones[i+1] );//IMPORTANT!!! 理解dp[i][j]的含义。
    for( int len = 2; len < n; len++ ){
        for( int begin = 0; begin+len < n; begin++ ){
            int left = presum[begin+len+1] - presum[begin+1] - dp[begin+1][begin+len];
            int right = presum[begin+len] - presum[begin] - dp[begin][begin+len-1];
            dp[begin][begin+len] = max( left, right );
        }
    }
    return dp[0][n-1];
}

int main(){
    vector<int> stones = { 1,100,3 };
    cout<<stone_game_minimum_diff( stones )<<endl;
    cout<<stone_game_maximum_diff( stones)<<endl;
    return 0;
}