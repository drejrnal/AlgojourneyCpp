//
// Created by luoxiYun on 2021/8/20.
//

/*
 * 记忆化搜索 相关问题
 * 力扣576
 *There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn].
 * You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary).
 * You can apply at most maxMove moves to the ball.Given the five integers m, n, maxMove, startRow, startColumn,
 * return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.
 */

#include "common.h"

class Solution {
    vector<vector<int>> move = {
            {-1, 0}, {1, 0},
            {0, -1}, {0, 1}
    };
    int cache[51][51][51];
    int MOD = 1000000007;
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        memset( cache, -1, sizeof(cache) );
        //明确每个点的状态，存储当前状态下已经计算好的值。
        return dfs( startRow, startColumn, m, n,  maxMove );
    }
    long long dfs( int startRow, int startColumn, int m, int n,  int movable ){
        if( movable < 0 )
            return 0;

        if( startColumn < 0 || startRow < 0 || startRow == m || startColumn == n ){
            return 1;
        }
        if( cache[startRow][startColumn][movable] != -1 )
            return cache[startRow][startColumn][movable];
        long long result = 0;
        for( int i = 0; i < 4; i++ )
            result =(result + dfs( startRow + move[i][0], startColumn + move[i][1], m, n, movable-1 )) % MOD;
        cache[startRow][startColumn][movable] = result;
        return result;
    }
};