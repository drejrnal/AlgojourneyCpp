//
// Created by luoxiYun on 2021/3/18.
//

#include "common.h"
#include <unordered_map>

class SmallestCover{

    unordered_map<char, int> window, candidate;

public:

    string minWindow( string &s, string &t ){
        int left = 0, right = 0;
        for( char ele : t )
            candidate[ele]++;
        while( right < s.length() ){
            if( candidate.count(s[right]) != 0 ){
                window[s[right]]++;
            }
            if( )
            right++;
        }
    }

};