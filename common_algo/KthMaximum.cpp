//
// Created by luoxiYun on 2021/3/11.
//

#include "common.h"

#include <cstdlib>
#include <ctime>

class kthMaximum{

public:

    int randomPartition( vector<int> &nums, int l, int r ){
        int pos = rand() % ( r - l + 1 ) + l;
        /*
         * 此处如果swap的参数是const的，则函数编译出错
         */
        std::swap( nums[pos], nums[r] );
        return partition( nums, l, r );
    }

    int partition( vector<int> &nums, int l, int r ){
        int left = l - 1;
        int pivot = nums[r];
        for( int i = l; i < r; i++ ){
            if( nums[i] <= pivot ) {
                std::swap(nums[++left], nums[i]);
            }
        }
        std::swap( nums[left+1], nums[r] );
        //nums[l...left+1] <= x < nums[left+2...r]
        return left+1;
    }

    int quickSelect( vector<int> &nums, int l, int r, int k){
        int pos = randomPartition( nums, l, r );
        if( pos == k )
            return nums[pos];
        else if( pos < k )
            return quickSelect( nums, pos+1, r, k );
        else
            return quickSelect( nums, l, pos - 1, k );
    }

    int findKth( vector<int> &nums, int k ){
        srand(time(0));
        int l = 0, r = nums.size() - 1;
        return quickSelect( nums, l, r, nums.size() - k );
    }




};

/*
int main(){
    kthMaximum kmm;
    vector<int> nums = { 3,2,3,1,2,4,5,5,6 };
    int k = 4;
    cout<<kmm.findKth( nums, k )<<endl;
    return 0;
}
 */