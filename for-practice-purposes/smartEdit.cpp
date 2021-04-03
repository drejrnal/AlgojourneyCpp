//
// Created by luoxiYun on 2021/3/11.
//

#include "include/common.h"

string edit(string s){
    string ans = "";
    int state = 0;
    char cur, prev = s[0];
    ans +=s[0];

    for( int i = 1; i < s.length(); i++){
        cur = s[i];
        switch (state) {
            case 0:
                if( prev == cur )
                    state = 1;
                else
                    state = 0;
                break;
            case 1:
                if( prev == cur ) //AAA
                    continue;
                else
                    state = 2;
                break;
            case 2:
                if( prev == cur ) //AABB
                    continue;
                else
                    state = 0;
                break;
            default:
                break;
        }
        ans +=cur;
        prev = cur;

    }

    return ans;
}

int main(){

    int cnt;
    cin>>cnt;
    while( cnt-- ){
        string orig;
        cin>>orig;
        cout<<edit(orig)<<endl;
    }
    return 0;
}