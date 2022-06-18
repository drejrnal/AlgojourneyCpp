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
/*
 * 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u',
 * 在子字符串中都恰好出现了偶数次。
 */
int findLongestSubstring( string s ){
    vector<int> pre( 1 << 5, -1 );
    int status = 0;
    int res = 0;
    pre[status] = 0;
    for( int i = 0; i < s.length(); i++ ){
        switch (s[i]) {
            case 'a':
                status ^= ( 1<<0 );
                break;
            case 'e':
                status ^= ( 1<<1 );
                break;
            case 'i':
                status ^= ( 1<<2 );
                break;
            case 'o':
                status ^= ( 1<<3 );
                break;
            case 'u':
                status ^= ( 1<<4 );
                break;
            default:
                break;
        }
        if( pre[status] >= 0 )
            res = max( res, i + 1 - pre[status] );
        else
            pre[status] = i+1;
    }
    return res;
}

int main(){
    string s;
    while ( cin>> s ){
        cout<<longest_repeatable_string(s)<<endl;
    }
    return 0;
}