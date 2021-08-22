//
// Created by luoxiYun on 2021/8/19.
//

#include "common.h"

long long substrings_including_consecutive_ones( string str, int k ){
    /*
     * k == 0 单独计算
     */
    if( k == 0 ){
        long long number0 = 0, res = 0;
        for( int i = 0; i < str.size(); i++ ){
            if( str[i] == '0' )
                number0++;
            else{
                res +=( number0 * (number0+1) )/2;
                number0 = 0;
            }
        }
        res +=( number0 * (number0+1) )/2;
        return res;
    }
    int left = 0, right = 0;
    int len = str.length();
    int cnt = 0, res = 0;
    while ( right < len ){
        while ( right < len && cnt != k ){
            if( str[right] == '1' )
                cnt++;
            if( cnt == k )
                break;
            right++;
        }
        if( right == len )
            break;
        res +=1;
        int bound = right + 1;
        while ( bound < len && str[bound] == '0' ) {
            res += 1;
            bound++;
        }
        if( str[left] == '1' ){
            cnt--;
            right++;
        }
        left++;
    }
    return res;
}

int main(){
    int k;
    cin>>k;
    string str;
    cin>>str;
    cout<<substrings_including_consecutive_ones( str, k )<<endl;
    return 0;
}