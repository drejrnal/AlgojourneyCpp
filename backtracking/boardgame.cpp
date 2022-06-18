//
// Created by luoxiYun on 2021/9/15.
//

/*
 * 收录一些需要在棋盘上进行操作的题目
 */
#include "common.h"

class backtrack_on_chessboard{
    //遍历的方向：上 下 左 右 左上 左下 右上 右下
    int row_direction[8] = { -1, 1, 0, 0, -1, 1, -1, 1};
    int col_direction[8] = { 0, 0, -1, 1, -1, -1, 1, 1};

    int rows;
    int cols;
    bool check( int cur_row, int cur_col ){
        return ( cur_row >= 0 && cur_row < rows ) && ( cur_col >= 0 && cur_col < cols );
    }

public:
    vector<vector<char>> updateBoard( vector<vector<char>> &board, vector<int>& click ){
        this->rows = board.size();
        this->cols = board[0].size();
        vector<vector<char>> result( board );
        dfs_on_landmine_board( result, click[0], click[1] );
        return result;
    }
    bool dfs_on_landmine_board( vector<vector<char>> &board, int cur_row, int cur_col ){
        if( board[cur_row][cur_col] == 'E') {
            int num_of_landmine = 0;
            int next_row = -1, next_col = -1;
            for( int i = 0; i < 8; i++ ){
                next_row = cur_row+row_direction[i];
                next_col = cur_col+col_direction[i];
                if(check( next_row, next_col)){
                    num_of_landmine +=( board[next_row][next_col] == 'M' ? 1 : 0 );
                }
            }
            if( num_of_landmine != 0 ){
                board[cur_row][cur_col] = num_of_landmine + '0';
            }else {
                board[cur_row][cur_col] = 'B';
                for( int i = 0; i < 8; i++ ) {
                    next_row = cur_row+row_direction[i];
                    next_col = cur_col+col_direction[i];
                    if(check(next_row, next_col))
                        if(dfs_on_landmine_board(board, next_row, next_col))
                            return true;
                }
            }
        } else if( board[cur_row][cur_col] == 'M' ){
            board[cur_row][cur_col] = 'X';
            return true;
        }
        return false;
    }
    /**
     * 棋盘里有黑白棋 若连续的白旗被黑棋包围，则白旗转黑，求在棋盘哪个位置上放置一枚黑旗后翻转白旗数目最多
     */
    int flipChess( vector<string>& chessboard ){
        rows = chessboard.size();
        cols = chessboard[0].size();
        int ans = 0;
        for( int i = 0; i < rows; i++ ){
            for( int j = 0; j < cols; j++ ){
                if( chessboard[i][j] == '.' ){
                    vector<string> copyboard( chessboard );
                    copyboard[i][j] = 'X';
                    ans = max( ans, dfs_on_chessboard(copyboard, i, j) );
                }
            }
        }
        return ans;
    }
    int dfs_on_chessboard( vector<string> &board, int cur_row, int cur_col ){
        int res = 0;
        for( int k = 0; k < 8; k++ ){
            int next_row = cur_row + row_direction[k], next_col = cur_col + col_direction[k];
            while (check(next_row, next_col) && board[next_row][next_col] == 'O' ){
                next_row +=row_direction[k];
                next_col +=col_direction[k];
            }
            int r = cur_row+row_direction[k], c = cur_col+col_direction[k];
            if( check(next_row, next_col) && (r != next_row || c != next_col) &&
                    board[next_row][next_col] == 'X' ){
                for(;(r != next_row || c != next_col) && board[r][c] != 'X'; r +=row_direction[k], c +=col_direction[k] ){
                    board[r][c] = 'X';
                    res++;
                    res += dfs_on_chessboard( board, r, c );
                }
            }
        }
        return res;
    }
    /*
     * grid illumination (lc 1001)
     * 解法中对行、列、对角线的计数与求解八皇后问题相似
     */
    vector<int> gridIllumination( int n, vector<vector<int>> &lamps, vector<vector<int>> &queries ){
        rows = cols = n;
        unordered_map<int, int> row, col, diagonal, reverse_diagonal;
        unordered_set<long long> lamps_on;
        vector<int> res;
        for( auto &lamp_pos : lamps ){
            //题目中台灯有重复元素，所以需要去重逻辑
            if( lamps_on.find( lamp_pos[0] * n + lamp_pos[1]) == lamps_on.end() ) {
                lamps_on.insert(lamp_pos[0] * n + lamp_pos[1]);
                row[lamp_pos[0]] += 1;
                col[lamp_pos[1]] += 1;
                diagonal[lamp_pos[0] - lamp_pos[1] + n - 1] += 1;
                reverse_diagonal[lamp_pos[0] + lamp_pos[1]] += 1;
            }
        }
        for( auto &query : queries ){
            int cur_row = query[0], cur_col = query[1];
            if( lamps_on.find(cur_row * n + cur_col) != lamps_on.end() )
                res.push_back(1);
            else if( row[cur_row] > 0 || col[cur_col] > 0
                        || diagonal[cur_row-cur_col+n-1] > 0 || reverse_diagonal[cur_row+cur_col] > 0 )
                res.push_back(1);
            else
                res.push_back( 0 );

            /*
             * 需要单独考虑查询的位置上刚好是一只灯泡的情况
             */
            if(check(cur_row, cur_col) && lamps_on.find(cur_row * n + cur_col) != lamps_on.end() ){
                lamps_on.erase(cur_row * n + cur_col);
                row[cur_row] -=1;
                col[cur_col] -=1;
                diagonal[cur_row - cur_col + n - 1] -=1;
                reverse_diagonal[ cur_row+cur_col ] -=1;
            }
            for( int k = 0; k < 8; k++ ){
                int next_row = cur_row + row_direction[k], next_col = cur_col + col_direction[k];
                if(check(next_row, next_col) && lamps_on.find(next_row * n + next_col) != lamps_on.end() ){
                    lamps_on.erase(next_row * n + next_col);
                    row[next_row] -=1;
                    col[next_col] -=1;
                    diagonal[next_row - next_col + n - 1] -=1;
                    reverse_diagonal[ next_row + next_col] -=1;
                }
            }
        }
        return res;
    }

};

int main(){
    vector<vector<char>> board = {
            {'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E'}
    };
    vector<string> chessboard = { ".......",".......",".......","X......",".O.....","..O....","....OOX" };
    backtrack_on_chessboard chess_game;
    //cout<<chess_game.flipChess( chessboard );
    /*vector<int> click = { 1, 2 };
    vector<vector<char>> res = chess_game.updateBoard(board,click );
    for( auto &arr : res ){
        for( char c : arr )
            cout<<c<<" ";
        cout<<endl;
    }*/
    vector<vector<int>> lamps = {
            {0,0},
            {0,1}
    };
    vector<vector<int>> queries = {
            {1,1},
            {0,0}
    };
    vector<int> ans = chess_game.gridIllumination( 5, lamps, queries );
    for( int ele : ans )
        cout<<ele<<" ";
    return 0;
}