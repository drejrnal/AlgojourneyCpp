//
// Created by luoxiYun on 2021/8/22.
//

#include "common.h"

int main(){
    int examples;
    cin>>examples;
    while ( examples-- ){
        int state;
        cin>>state;
        vector<vector<double>> transform_matrix(3, vector<double>(3) );
        vector<vector<double>> result( state+1, vector<double>(3) );
        for( int i = 0; i < 3; i++ )
            cin>>result[0][i];
        for( int i = 0; i < 3; i++ ){
            for( int j = 0; j < 3; j++ )
                cin>>transform_matrix[i][j];
        }
        for( int i = 1; i <= state; i++ ){
            //计算result[i][0] result[i][1] result[i][2]
            result[i][0] = transform_matrix[0][0] * result[i-1][0] +
                    transform_matrix[0][1] * result[i-1][1] +
                    transform_matrix[0][2] * result[i-1][2];
            result[i][1] = transform_matrix[1][0] * result[i-1][0] +
                           transform_matrix[1][1] * result[i-1][1] +
                           transform_matrix[1][2] * result[i-1][2];
            result[i][2] = transform_matrix[2][0] * result[i-1][0] +
                           transform_matrix[2][1] * result[i-1][1] +
                           transform_matrix[2][2] * result[i-1][2];
        }
        //cout<< result[state][1] <<endl;
        cout<< (result[state][2] > 0.5) ? 1 : 0;
    }
    return 0;
}