//
// Created by luoxiYun on 2021/7/29.
//
/*
 * 力扣跳跃游戏系列
 */
#include "common.h"
class JumpGame {
public:
    /*
     * 力扣 题目55
     * 判断从起点是否可跳跃到末端点
     * 动态规划 超时
     */
    bool canJumpToLastPoint( vector<int> &nums ){
        vector<bool> dp( nums.size(), false );
        dp[0] = true;
        for( int i = 1; i < nums.size(); i++ ){
            for( int j = 0; j < i; j++ ){
                if( nums[j] > 0 ){
                    if( j + nums[j] >= i ){
                        dp[i] = dp[i] | dp[j];
                        if( dp[i] )
                            break;
                        break;
                    }
                }
            }
        }
        return dp[nums.size()-1];
    }
    //贪心策略
    bool canJumpGreedy(vector<int>& nums) {
        int farthest = nums[0];
        for( int i = 1; i < nums.size() - 1; i++ ){
            if( i > farthest ) //当前位置比最远位置大，说明无法通过之前的节点到达该点，结束循环
                break;
            if( i + nums[i] > farthest ) //当前i位置可达，并判断是否需要更新最远可到达节点
                farthest = i + nums[i];
        }
        return farthest >= nums.size()-1;
    }
    /*
     * 力扣45 假设保证可跳到末端点，求跳到尾端点的最小跳跃次数
     * 错误的贪心策略: 每当最远距离更新时，更新跳跃次数。
     * 这种策略错误的实例：[7,0,9,6,9,6,1,7,9,0,1,2,9,0,3]
     * int jump(vector<int>& nums) {
        if( nums.size() == 0 || nums.size() == 1 )
            return 0;
        int res = 1;
        int n = nums.size()-1;
        int rightest = nums[0];
        for( int i = 1; i <= n; i++ ){
            //rightest = max( rightest, i + nums[i] );
            if( rightest >= n )
                break;
            if( rightest < i + nums[i] ){
                rightest = i + nums[i];
                res++;
            }
        }
        return res;
    }
     */
    int minimum_jump(vector<int>& nums) {
        int prev_righest = 0;
        int righest = 0;
        int res = 0;
        for( int i = 0; i < nums.size()-1; i++ ){
            righest = max( righest, nums[i]+i );
            if( i == prev_righest ){
                prev_righest = righest;
                res++;
            }
        }
        return res;
    }

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
        //此时未到达值为0的点，且visit[start]为true，说明则从该start左右跳的结果不会到达值为0的点（之前的遍历计算该结果）
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