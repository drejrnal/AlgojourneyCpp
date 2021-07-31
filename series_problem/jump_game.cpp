//
// Created by luoxiYun on 2021/7/29.
//
/*
 * 力扣跳跃游戏系列
 */
#include "common.h"
class JumpGame {
public:
    bool canJumpToZeroPoint(vector<int> &arr, int start) {
        vector<bool> visited(arr.size(), false);
        vector<bool> onStack( arr.size(), false );
        return dfs(arr, start, visited, onStack );
    }
    bool dfs( vector<int> &arr, int start, vector<bool> &visited, vector<bool> &onStack ){
        if( onStack[start] )
            return false;
        if( arr[start] == 0 )
            return true;
        bool left = false, right = false;
        if( !visited[start] ) {
            onStack[start] = true;
            visited[start] = true;
            if( start - arr[start] >= 0 )
                left = dfs( arr, start - arr[start], visited, onStack );
            if( left )
                return true;
            if( start + arr[start] < arr.size() )
                right = dfs( arr, start + arr[start], visited, onStack );
            if( right )
                return true;
            onStack[start] = false;
        }
        return false;
    }
};

int main(){
    vector<int> arr = { 3,0,2,1,2};
    JumpGame jumpGame;
    cout<<jumpGame.canJumpToZeroPoint( arr, 2 )<<endl;
    return 0;
}
