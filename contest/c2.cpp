//
// Created by luoxiYun on 2021/3/28.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Solution{
public:
    string evaluate(string &s, vector<vector<string>>& knowledge){
        map<string, string> table;
        for( auto &value : knowledge ){
            table[value[0]] = value[1];
        }
        string res = "";
        int trav = 0;
        int size = s.length();
        while( trav < size ){
            if( s[trav] == '(' ){
                int right = trav;
                while( right < s.length() && s[right] != ')' )
                    right++;
                string tmp = s.substr( trav+1, right - trav - 1 );
                if( table.find(tmp) != table.end() )
                    res +=table[tmp];
                else
                    res +="?";
                trav = right+1;
            }else {
                res += s[trav];
                trav++;
            }
        }
        return res;
    }
};

int main(){
    string s = "(name)is(age)yearsold";
    vector<vector<string>> know = {
            {"name","bob"},
            {"age","two"}
    };
    Solution solution;
    cout<<solution.evaluate(s, know)<<endl;
    return 0;
}