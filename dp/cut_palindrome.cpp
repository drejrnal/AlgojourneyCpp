//
// Created by luoxiYun on 2021/3/9.
//

#include "common.h"

class CutPalindrome{

    vector<vector<bool>> check;

public:
    void checkPalindrome( string& s ){
        check = vector<vector<bool>>( s.length(), vector<bool>(s.length(),false ));
        for( int len = 1; len <= s.length(); len++ ){
            for( int i = 0; i < s.length(); i++ ){
                int  j = i+len-1;
                if ( j < s.length() ) {
                    if (s[i] == s[j]) {
                        if (i == j || (j == i + 1))
                            check[i][j] = true;
                        else {
                            check[i][j] = check[i + 1][j - 1];
                        }
                    } else {
                        check[i][j] = false;
                    }
                }
            }
        }
    }

    bool isPalindrome(int left, int right){
        return check[left][right];
    }

    int cutIntoPalindrome( string &s ){
        vector<int> dp(s.length(), INT32_MAX);
        //初始化dp[0..len-1]
        for( int i = 0; i < s.length(); i++)
            if( isPalindrome( 0, i) )
                dp[i] = 0;
        /*
         * 最长递增子序列的模板
         */
        for( int i = 1; i < s.length(); i++ ){
            for( int j = 0; j < i; j++){
                if( isPalindrome(j+1, i)){
                    dp[i] = min( dp[j] + 1, dp[i] );
                }
            }
        }
        return dp[s.length()-1];
    }

};

/*
int main(int argc, char *argv[]){
    CutPalindrome cutPalindrome;
    string s(argv[1]);
    cutPalindrome.checkPalindrome(s);
    cout<<cutPalindrome.cutIntoPalindrome(s)<<endl;
    return 0;

}
 */