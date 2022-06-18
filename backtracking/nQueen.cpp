//
// Created by luoxiYun on 2021/3/17.
//

#include "common.h"

class NQueens{
    int N;
    vector<vector<string>> layout;
public:
    NQueens( int N_ ):N(N_){}
    /*
     * @Param diagnal1 主对角线
     * @Param diagnal2 副对角线
     */
    void dfs( int row, unordered_set<int> &cols, unordered_set<int> diagnal1,
                unordered_set<int> &diagnal2, vector<int> &column){
        if( row == N ){
            //递归终止
            for( int i = 0; i < N; i++ ){
                for( int j = 0; j < N; j++ ){
                    if( column[i] == j )
                        cout<<"Q"<<" ";
                    else
                        cout<<"."<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
            return;
        }
        for( int i = 0; i < N; i++ ){
            if( cols.count(i) != 0 || diagnal1.count(row - i) != 0 || diagnal2.count(row + i) != 0 )
                continue;
            cols.insert( i );
            diagnal1.insert( row - i );
            diagnal2.insert( row + i);
            column.push_back( i );
            dfs( row + 1, cols, diagnal1, diagnal2, column );
            cols.erase( i );
            diagnal1.erase( row - i );
            diagnal2.erase( row + i);
            column.pop_back();
        }
    }
    //使用状态压缩进行dfs(将布尔数组转换成整数)
    void dfs( int row, int col, int diagonal, int reverse_diagonal, vector<int> &column ){
        if( row == N ){
            vector<string> res;
            for( int i = 0; i < N; i++ ){
                int col = column[i];
                string row = "";
                for( int j = 0; j < N; j++ ) {
                    if (j == col)
                        row +="Q";
                    else
                        row +=".";
                }
                res.push_back( row );
            }
            layout.push_back( res );
            return;
        }
        for( int i = 0; i < N; i++ ){
            if( ((col >> i) & 1) || ((diagonal >> (row-i+N-1)) & 1) || ((reverse_diagonal >> (row+i)) & 1) )
                continue;
            column.push_back( i );
            col ^= ( 1 << i );
            diagonal ^= ( 1 <<( row - i + N -1) );
            reverse_diagonal ^= ( 1 << (row+i) );
            dfs( row+1, col, diagonal, reverse_diagonal, column );
            col ^= ( 1 << i );
            diagonal ^= ( 1 <<( row - i + N -1) );
            reverse_diagonal ^= ( 1 << (row+i) );
            column.pop_back();
        }

    }
    vector<vector<string>> solveNQueen( int n ){
        vector<int> column;
        dfs( 0, 0, 0, 0, column );
        return layout;
    }

};

int main( ){
    int n;
    cin>>n;
    NQueens nQueens(n);
//    unordered_set<int> cols, diagnal1, diagnal2;

    //nQueens.dfs(0, cols, diagnal1, diagnal2, column);
    vector<vector<string>> res = nQueens.solveNQueen( n );
    for( auto &arr : res ){
        for( auto &row : arr ){
            cout<<row<<" ";
        }
        cout<<endl;
    }
    return 0;
}
