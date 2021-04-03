//
// Created by luoxiYun on 2021/3/9.
//

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class PalinCheck{

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
};

/*
int main(int argc, char *argv[]){
    Solution s;
    vector<vector<bool>> ret = s.checkPalindrome(argv[1]);
    for( int i = 0; i < ret.size(); i++ ){
        for( int j = 0; j < ret.size(); j++){
            cout<<ret[i][j]<<" ";
        }
        cout<<endl;
    }
}
*/