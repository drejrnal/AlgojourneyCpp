//
// Created by luoxiYun on 2021/3/15.
//

#include "common.h"

class KMP{

public:

    vector<int> calcu_next( string &pattern ){
        vector<int> next(pattern.size(), 0);
        int begin = 1, matched = 0;
        while( begin + matched < pattern.size() ){
            if( pattern[begin+matched] == pattern[matched] ) {
                next[ begin+matched ] = matched+1;
                matched++;
            }else{
                if( matched == 0 )
                    begin++;
                else{
                    begin +=( matched - next[matched-1]);
                    matched = next[matched-1];
                }
            }
        }
        return next;
    }

    int kmpSearch( string &heyStack, string &needle ){
        int begin = 0, matched = 0;
        vector<int> next = calcu_next(needle);
        vector<int> res;
        while( begin + matched < heyStack.size() ){
            if( heyStack[begin+matched] == needle[matched] ){
                ++matched;
                if( matched == needle.size() ){

                    res.push_back(begin);
                    begin +=( matched - next[matched-1] );
                    matched = next[matched-1];
                }
            }else{
                if( matched == 0 )
                    ++begin;
                else{
                    begin +=( matched - next[matched-1] );
                    matched = next[matched-1];
                }
            }
        }
        for( int i = 0; i < res.size(); i++ ){
            cout<<heyStack.substr(res[i], needle.size() )<<endl;
        }
        return res.size();
    }
};
/*
int main(int argc, char *argv[]){
    string text = argv[1], pattern = argv[2];
    KMP kmp;
    cout<<kmp.kmpSearch(text, pattern)<<endl;
    return 0;
}
 */