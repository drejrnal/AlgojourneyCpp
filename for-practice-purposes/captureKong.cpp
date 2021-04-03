//
// Created by luoxiYun on 2021/3/12.
//

#include "include/common.h"

int result = 0;

void dfs( vector<int> &nums, int start, int prev, int distance, int depth ){
    if( depth == 3 ) {
        result = result % 99997867 + 1;
        return;
    }
    for( int i = start; i < nums.size(); i++ ){
        if( nums[i] - prev > distance )
            break;
        int remainDis = distance - ( nums[i] - prev );
        dfs( nums, i + 1, nums[i], remainDis, depth+1 );
    }
}
int solution( vector<int> nums , int distance){
    int left = 0, right = 1, res = 0;
    while( left < nums.size() - 2 ){
        while( right < nums.size() && nums[right] - nums[left] <= distance )
            right++;
        int num = right - 1 - left;

        if( num >= 2 ){
            res =(res % 99997867 + ( num * (num - 1) )/2) % 99997867;
        }
        left++;
    }
    return res;
}

int main(){
    vector<int> pos;
    int num, distance;
    cin>>num>>distance;
    while( num-- ){
        int ele;
        cin>>ele;
        pos.push_back(ele);
    }

    cout<<solution(pos, distance)<<endl;
    return 0;
}