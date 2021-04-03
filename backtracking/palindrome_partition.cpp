//
// Created by luoxiYun on 2021/3/9.
//

#include <vector>
#include <string>

using namespace std;
class PalinPartition {

    vector<vector<string>> result;

public:
    bool isPalindrome( string &s, int left, int right ){
        while( left < right ){
            if( s[left] != s[right] )
                return false;
            left++;
            right--;
        }
        return true;
    }

    void dfs( string &s, int start, vector<string> &path){
        int len = s.length();
        if( start == len ){
            result.push_back(path);
            return;
        }
        for( int index = start; index < len; index++) {
            if (isPalindrome(s, start, index)) {
                path.push_back(s.substr(start, index - start + 1));
                dfs(s, index + 1, path);
                path.pop_back();
            } else {
                continue;
            }
        }
        return;
    }

    vector<vector<string>> partition(string s) {
        vector<string> path;
        dfs( s, 0, path);
        return result;
    }
};
/*
int main(int argc, char *argv[]){
    Solution s;
    string str(argv[1]);
    s.partition(str);
    return 0;
}*/