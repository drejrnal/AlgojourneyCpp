//
// Created by luoxiYun on 2021/3/9.
//

#include "common.h"

using namespace std;

class palindrome_dynamic_programming{

public:
    vector<vector<bool>> checkPalindrome( string s ){
        vector<vector<bool>> dp( s.length(), vector<bool>(s.length(),false ));
        for( int len = 1; len <= s.length(); len++ ){
            for( int i = 0; i < s.length(); i++ ){
                int  j = i+len-1;
                if ( j < s.length() ) {
                    if (s[i] == s[j]) {
                        if (i == j || (j == i + 1))
                            dp[i][j] = true;
                        else {
                            dp[i][j] = dp[i + 1][j - 1];
                        }
                    } else {
                        dp[i][j] = false;
                    }
                }
            }
        }
        return dp;
    }

    //获取字符串内最长回文序列
    int longestPalindromeSubsequence( string str ){
        int len = str.length();
        vector<vector<int>> dp( len, vector<int>(len, 0) );
        for( int i = 0; i < len-1; i++ ){
            dp[i][i] = 1;
            dp[i][i+1] = (str[i] == str[i+1]) ? 2 : 1;
        }
        dp[len-1][len-1] = 1;
        for( int i = 3; i <= len; i++ ){
            for( int left = 0; left + i <= len; left++ ){
                int right = left + i - 1;
                if( str[left] == str[right] )
                    dp[left][right] = dp[left+1][right-1] + 2;
                else
                    dp[left][right] = max( dp[left][right-1], dp[left+1][right] );
            }
        }
        return dp[0][len-1];
    }
};


int main(int argc, char *argv[]){
    palindrome_dynamic_programming s;
    //vector<vector<bool>> ret = s.checkPalindrome(argv[1]);
    string str;
    cin>>str;
    cout<<s.longestPalindromeSubsequence(str)<<endl;
    return 0;
}