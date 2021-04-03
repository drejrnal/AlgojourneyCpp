//
// Created by luoxiYun on 2021/3/16.
//

#include "common.h"

class RobotWander{

    int count;
    int k;
    int row, col;
    int direction[4][2] = {
            { -1, 0}, { 1, 0 }, { 0, -1 }, { 0, 1 }
    };

public:

    RobotWander(int row_, int col_, int k_):row(row_), col(col_), k(k_){
        count = ( k >= 0) ? 1: 0;
    }

    inline int getCount(){
        return count;
    }

    inline int bitSum( int num ){
        int res = 0;
        while ( num > 0 ){
            res +=( num % 10 );
            num /= 10;
        }
        return res;
    }

    bool isValid( int x, int y ){
        return (bitSum( x ) + bitSum( y )) <= k;
    }

    int dfs( vector<vector<bool>> &visit, int x, int y ){
        if( x < 0 || x >= row || y < 0 || y >= col || visit[x][y] || !isValid(x, y) )
            return 0;
        int ret = 1;
        visit[x][y] = true;
        for( int i = 0; i < 4; i++ ){
            int nX = x + direction[i][0], nY = y + direction[i][1];
            ret +=dfs( visit, nX, nY );
        }
        return ret;
    }
};

/*
int main(){
    int row, col;
    int k;
    cin>>row>>col>>k;
    RobotWander robotWander( row, col, k );
    vector<vector<bool>> visit(row, vector<bool>(col, false));
    cout<<robotWander.dfs( visit, 0, 0 )<<endl;
    return 0;
}
*/