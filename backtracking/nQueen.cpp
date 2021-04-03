//
// Created by luoxiYun on 2021/3/17.
//

#include "common.h"
#include <unordered_set>
class NQueens{

    int N;
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

};
/*
int main( ){
    int n;
    cin>>n;
    NQueens nQueens(n);
    unordered_set<int> cols, diagnal1, diagnal2;
    vector<int> column;
    nQueens.dfs(0, cols, diagnal1, diagnal2, column);
    return 0;
}
 */