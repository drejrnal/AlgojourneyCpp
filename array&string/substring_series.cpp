//
// Created by luoxiYun on 2021/8/17.
//

#include "common.h"
/*
 * 超时写法
 */
int longest_repeatable_string_brutal( const string &str ){
    int begin = 0;
    int maximum_len = 0;
    for( int len = 1; len <= str.length()/2; len++ ){
        for( int i = 0; i+2*len<=str.length(); i++  ){
            string origin = str.substr( i, len );
            string copy_origin = str.substr( i + len, len );
            if( origin == copy_origin ){
                maximum_len = max(2*len, maximum_len);
            }
        }
    }
    return maximum_len;
}
/*
 * 给定子串长度len，不需求子串，而是以计数的方式记录以某一位置为起点，是否可构成长度为len的重复字符串
 */
int longest_repeatable_string( const string &str ){
    int maximum_len = 0;
    for(int len = 1 ; len <= str.length()/2; len++ ){
        int count = 0;
        for( int i = 0; i + len < str.length(); i++  ){
            if( str[i] == str[i+len] )
                count++;
            else
                count = 0;
            if( count == len ) {
                maximum_len = max(maximum_len, count * 2);
                break;
            }
        }
    }
    return maximum_len;
}
int main(){
    string s;
    while ( cin>> s ){
        cout<<longest_repeatable_string(s)<<endl;
    }
    return 0;
}