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

/**
 * 给定一个字符串pattern和一个字符串value，判断value是否符合pattern
 * 求解二元一次方程 lenA * numA + lenB * numB = m 其中m为value的长度, numA和numB为pattern中'a'和'b'的个数， 求解lenA和lenB
 * @param pattern 只由'a'和'b'组成
 * @param value
 * @return
 */

bool matchSinglePatternAlpha(size_t len, string& value){
    if (len == 0 || value.size() % len != 0)
        return false;
    string sub = value.substr(0, len);
    for( size_t i = len; i < value.size(); i += len ){
        if( value.substr(i, len) != sub )
            return false;
    }
    return true;
}
bool matchBiPatternAlpha(int num_a, int num_b, string& pattern, string& value){
    size_t m = value.size();
    for (int len_a = 0; len_a * num_a <= m; len_a++) {
        if ((m - len_a * num_a) % num_b != 0)
            continue;
        size_t len_b = (m - len_a * num_a) / num_b;
        size_t i = 0;
        string sub_a, sub_b;
        for (char c: pattern) {
            if (c == 'a') {
                if (sub_a.empty())
                    sub_a = value.substr(i, len_a);
                else if (value.substr(i, len_a) != sub_a)
                    break;
                i += len_a;
            } else {
                if (sub_b.empty())
                    sub_b = value.substr(i, len_b);
                else if (value.substr(i, len_b) != sub_b)
                    break;
                i += len_b;
            }
        }
        if (i == m && sub_a != sub_b)
            return true;
    }
    return false;
}
bool patternMatch(string pattern, string value){
    size_t m = value.size();
    int a = 0, b = 0;
    for( char c : pattern ){
        if( c == 'a' )
            a++;
        else
            b++;
    }
    if( a == 0 && b == 0 )
        return m == 0;
    if ( m == 0 )
        return a == 0 || b == 0;
    if (a == 0){
        return pattern[0] == 'b' && matchSinglePatternAlpha(m / b, value);
    }else if (b == 0){
        return pattern[0] == 'a' && matchSinglePatternAlpha(m / a, value);
    } else {
        return matchBiPatternAlpha(a, b, pattern, value);
    }
}

int main(){
    string s;
    while ( cin>> s ){
        cout<<longest_repeatable_string(s)<<endl;
    }
    return 0;
}