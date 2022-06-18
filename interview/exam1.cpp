//
// Created by luoxiYun on 2021/8/22.
//

#include "common.h"

int main(){
    int keys_num, locks_num;
    cin>>keys_num>>locks_num;
    vector<vector<int>> costs( keys_num, vector<int>(locks_num,-1) );
    vector<int> column( keys_num );
    double exception_time = 0.0;
    for( int i = 0; i < keys_num; i++ ){
        for( int j = 0; j < locks_num; j++ ){
            cin>>costs[i][j];
        }
    }
    for( int i = 0; i < locks_num; i++ ){
        for( int j = 0; j < keys_num; j++ ){
            column[j] = costs[j][i];
        }
        sort( column.begin(), column.end() );
        int keys = keys_num;
        for( int index = 0; index < column.size(); index++ ){
            exception_time +=( static_cast<double>( column[index] * keys ) /keys_num );
            keys--;
        }
    }
    cout<<exception_time<<endl;
    return 0;
}