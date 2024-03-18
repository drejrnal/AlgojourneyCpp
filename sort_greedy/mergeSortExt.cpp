//
// Created by luoxiYun on 2021/6/1.
//

#include "common.h"

class mergeSortVar{

public:
    int totalCnt = 0;
public:
    void mergeVar( int left, int mid, int right,vector<long long> &pre_sum, int lower, int upper ) {
        long long tmpArr[right - left + 1];
        int left_ptr = left, right_ptr = mid + 1;
        int cnt_left = right_ptr, cnt_right = right_ptr;
        while( left_ptr <= mid ) {

            while (cnt_left <= right && pre_sum[cnt_left] - pre_sum[left_ptr] < lower){
                //此时下标在(cnt_left)前的arr元素小于tmp_lower
                cnt_left++;
            }
            //cnt_right = cnt_left;注意cnt_right和cnt_left都是逐渐增大的，因此不存在回退的情况，像此处这种回退操作这么写会超时
            while (cnt_right <= right && pre_sum[cnt_right] - pre_sum[left_ptr] <= upper){
                //此时下标在[cnt_right]后的arr元素大于tmp_upper
                cnt_right++;
            }
            totalCnt += ( cnt_right - cnt_left );
            left_ptr++;

        }
        left_ptr = left;
        right_ptr = mid + 1;
        int tmp_i = 0;
        while( left_ptr <= mid && right_ptr <= right ){
            if( pre_sum[left_ptr] < pre_sum[right_ptr] ){
                tmpArr[tmp_i++] = pre_sum[left_ptr++];
            } else {
                tmpArr[tmp_i++] = pre_sum[right_ptr++];
            }
        }
        while( left_ptr <= mid )
            tmpArr[tmp_i++] = pre_sum[left_ptr++];
        while ( right_ptr <= right )
            tmpArr[tmp_i++] = pre_sum[right_ptr++];

        for( int i = 0; i <= right - left; i++ ){
            pre_sum[ left + i ] = tmpArr[i];
        }
    }

    void dividVar( int left, int right, vector<long long> &pre_sum, int lower, int upper ){
        if( left == right ){
            if( pre_sum[left] <= upper && pre_sum[right] >= lower )
                totalCnt +=1;
            return;
        }
        int mid = left + ( right - left )/2;
        dividVar( left, mid, pre_sum, lower, upper );
        dividVar( mid + 1, right, pre_sum, lower, upper );
        mergeVar( left, mid, right, pre_sum, lower, upper );
    }

    int countRangeSum( vector<long long> &pre_sum, int lower, int upper) {
        dividVar(  1, pre_sum.size()-1,pre_sum, lower, upper );
        return totalCnt;
    }

    void mergeSort( vector<int> &nums, int left, int right ) {
        if (left == right)
            return;
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
    //now use external sort to implement merge function
    void merge( vector<int> &nums, int left, int mid, int right ) {
        vector<int> tmpArr(right - left + 1);
        int left_ptr = left, right_ptr = mid + 1;
        int tmp_i = 0;
        while (left_ptr <= mid && right_ptr <= right) {
            if (nums[left_ptr] < nums[right_ptr]) {
                tmpArr[tmp_i++] = nums[left_ptr++];
            } else {
                tmpArr[tmp_i++] = nums[right_ptr++];
            }
        }
        while (left_ptr <= mid)
            tmpArr[tmp_i++] = nums[left_ptr++];
        while (right_ptr <= right)
            tmpArr[tmp_i++] = nums[right_ptr++];
        for (int i = 0; i <= right - left; i++) {
            nums[left + i] = tmpArr[i];
        }
    }

};

int main(){
    mergeSortVar mergeVar;
    //32位整数边界case
    vector<int> nums = { -2147483647,0,-2147483647,2147483647 };
    int lower = -564, upper = 3864;
    //此处prefix_sum类型为64位整形，否则溢出
    vector<long long> prefix_sum(nums.size()+1, 0);
    for( int i = 1; i < prefix_sum.size(); i++ )
        prefix_sum[i] =prefix_sum[i-1] + nums[i-1];
    cout<<mergeVar.countRangeSum( prefix_sum, lower, upper )<<endl;
    for( long long num : prefix_sum )
        cout<<num<<" ";
    return 0;
}