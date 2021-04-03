//
// Created by luoxiYun on 2021/3/10.
//

#include "common.h"

class calcuSubset{
    vector<vector<int>> res;
public:
    void dfs( int start, vector<int> &path, const vector<int> &nums ){
        res.push_back( path );
        int prev = INT32_MAX;
        for( int i = start; i < nums.size(); i++){
            /*
             * 递归分支中，若当前分支数字与前一分支数字相同，则剪掉该分支
             */
            if( nums[i] == prev )
                continue;
            prev = nums[i];
            path.push_back( nums[i] );
            /*
             * 易错点：注意此处dfs递归下一层是i + 1，而不是start + 1
             */
            dfs( i+1, path, nums );
            path.pop_back();
        }
    }
    vector<vector<int>> subsetWithDup(vector<int>& nums) {
        vector<int> path;
        sort( nums.begin(), nums.end() );
        dfs( 0, path, nums );
        return res;
    }
    vector<vector<int>> subsetsNoDup(vector<int>& nums) {
        vector<int> path;
        dfs( 0, path, nums );
        return res;
    }
};
/*
int main( int argc, char *argv[]){
    calcuSubset cls;
    vector<int> nums = { 1, 2, 3,2 };
    auto res = cls.subsetWithDup(nums);
    for( int i = 0; i < res.size(); i++){
        for( int j = 0; j < res[i].size(); j++ ){
            cout<<res[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
 */