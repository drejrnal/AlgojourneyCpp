//
// Created by luoxiYun on 2021/3/27.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> isPalindrome( vector<int> &nums, int left, int right ){
    int res = 0, l, r;
    while( left < right ){
        if( nums[left] != nums[right] ) {
            if( res == 0 ){
                l = left; r = right;
            }
            res +=1;
        }
        left++;
        right--;
    }
    return { l, r, res };
}

int main(){
    int examples;
    cin>>examples;
    while( examples-- ){
        int n;
        cin>>n;
        vector<int> numbers(n);
        string line;
        cin>>line;
        for (int i = 0; i < n; ++i) {
            numbers[i] = line[i] - '0';
        }
        string res = "";
        vector<int> is_palin = isPalindrome(numbers, 0, n - 1);
        if( is_palin[2] == 0 ){

        }else if( is_palin[2] == 1 ){
            int left = is_palin[0], right = is_palin[1];
            if( numbers[left] < numbers[right] )
                numbers[right] = numbers[left];
            else
                numbers[left] = numbers[right];
        }else{
            int topEndian = 0;
            int min_ele = *min_element( numbers.begin(), numbers.end() );
            while ( topEndian != n ){
                if( numbers[topEndian] != min_ele ) {
                    numbers[topEndian] = min_ele;
                    break;
                }
                topEndian++;
            }
        }
        for (int i = 0; i < n; ++i) {
            res +=to_string(numbers[i]);
        }
        cout<<res<<endl;
    }
    return 0;
}