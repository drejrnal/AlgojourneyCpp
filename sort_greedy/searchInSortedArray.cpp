//
// Created by luoxiYun on 2021/6/13.
//

/*
 * 有序数组使用二分法求目标值所在位置
 * 将有序数组旋转后，数组部分有序，若要寻找某目标值，依然可以使用二分
 */

#include "common.h"

class biSearchInArray{

public:
    //有序数组旋转后，寻找数组中某一目标值
    /*
     * 边界case: nums[4,5,6,7,0,1,2] target = 2或4
     *  出错原因：没有考虑target == nums[0]或target == nums[nums.size()-1]时的情况
     *  解决方式：
     *      if( target > nums[0] && target < nums[mid] )改成if( target >= nums[0] && target < nums[mid] )
     *      if( target > nums[mid] && target < nums[nums.size()-1] )改成if( target > nums[mid] && target <= nums[nums.size()-1] )
     * 边界case nums[3,1] target = 1,
     *  出错原因：没有考虑nums[mid] == nums[0]情况下的情况
     *  nums[0] == nums[mid]出现
     *      1. 要么二分后仅有一个元素，此时通过nums[mid]与target判断是否相等即可
     *      2. 要么二分后有两个元素，此时如果nums[mid] != target时，low = mid + 1；循环下一步判断nums[mid]与target是否相等
     *  解决方式：if( nums[mid] > nums[0] )改成if( nums[mid] >= nums[0] )
     */
    int searchInRotatedArray( vector<int> &nums, int target ){
        int low = 0, high = nums.size() - 1;
        while( low <= high ){
            int mid = low + ( high - low )/2;
            if( target == nums[mid] )
                return mid;
            if( nums[mid] >= nums[0] ){
                if( target >= nums[0] && target < nums[mid] )
                    high = mid - 1;
                else
                    low = mid + 1;
            }else{
                if( target > nums[mid] && target <= nums[nums.size()-1] )
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return -1;
    }
    /*
     * 数组内有重复元素，与上一个函数不同的是target同nums[left]和nums[high]比较大小，
     * 而非nums[0]和nums[nums.size()-1]
     */
    bool searchInRotatedArrayWithDup( vector<int> &nums, int target ){
        int low = 0, high = nums.size() - 1;
        while( low <= high ){
            int mid = low + ( high - low )/2;
            if( target == nums[mid] )
                return true;
            if( nums[mid] > nums[low] ){
                if( target >= nums[low] && target < nums[mid] )
                    high = mid - 1;
                else
                    low = mid + 1;
            }else if( nums[mid] < nums[low] ){
                if( target > nums[mid] && target <= nums[high] )
                    low = mid + 1;
                else
                    high = mid - 1;
            }else{
                low++;
            }
        }
        return false;
    }
    /*
     * bad case: nums[-1, 0, 0, 3, 7, 8, 11, 16, 16, 18, 19, 23, -22,
     * -20, -20, -19, -18, -12, -11, -7, -6, -4, -2]
     *  154494562
     */
    int searchLowestInRotatedArray( vector<int> &nums, int target ){
        int low = 0, high = nums.size() ;
        while( low < high ){
            int mid = low + ( high - low )/2;
            if( target == nums[low] )
                return low;
            //if( target == nums[mid] )
            //    high = mid;
            if( nums[mid] > nums[low] ){
                if( target >= nums[low] && target <= nums[mid] )
                    high = mid;
                else
                    low = mid + 1;
            }else if( nums[mid] < nums[low] ){
                if( target > nums[mid] && target <= nums[high-1] )
                    low = mid + 1;
                else
                    high = mid;
            }else{
                low++;
            }
        }
        if( low == nums.size() ) return -1;
        return nums[low] == target ? low : -1;
    }

};

int main(){
    vector<int> nums = { -1, 0, 0, 3, 7, 8, 11, 16, 16, 18, 19, 23, -22,
                          -20, -20, -19, -18, -12, -11, -7, -6, -4, -2 };
    int target = -1;
    biSearchInArray biSearch;
    cout<<biSearch.searchLowestInRotatedArray( nums, target )<<endl;
    return 0;
}