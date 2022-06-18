//
// Created by luoxiYun on 2021/4/10.
//

/*
 * 网格内进行dfs
 * 对应力扣 130、1020题目
 */
#include "common.h"

class GridDfsSearch{
    vector<vector<int>> move = {
            //上、下、左、右
            {-1, 0}, {1, 0},
            {0, -1}, {0, 1}
    };

public:
    void dfs( vector<vector<int>> &grid, int node_x, int node_y ){
        if( node_x < 0 || node_y <0 || node_x == grid.size() || node_y == grid[0].size() )
            return;
        if( grid[node_x][node_y] == 0 )
            return;
        grid[node_x][node_y] = 0;
        for( int i = 0; i < 4; i++ ) {
            dfs(grid, node_x + move[i][0], node_y + move[i][1] );
        }
    }

    int numEnclaves(vector<vector<int>>& grid) {
        int res = 0;
        //列遍历
        for( int i = 0; i < grid[0].size(); i++ ){
            dfs( grid, 0, i );
            dfs( grid, grid.size()-1, i );
        }
        for( int i = 1; i < grid.size() - 1; i++ ){
            dfs( grid, i, 0 );
            dfs( grid, i, grid[0].size()-1 );
        }
        for( int i = 0; i < grid.size(); i++ ){
            for( int j = 0; j < grid[0].size(); j++ ){
                if( grid[i][j] == 1 )
                    res++;
            }
        }
        return res;
    }
};

int main(){
    vector<vector<int>> grid = {
            {0,1,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,0,0}
    };
    GridDfsSearch gridDfsSearch;
    cout<<gridDfsSearch.numEnclaves( grid )<<endl;
    return 0;
}