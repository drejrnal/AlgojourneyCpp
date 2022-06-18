//
// Created by luoxiYun on 2021/9/13.
//

#include "common.h"

int maximum_even_sum( vector<int> &cards, int cnt ){
    sort( cards.begin(), cards.end());
    int res;
    int min_even_sub = -1;
    int min_odd_sub = -1;
    for( int i = cards.size() - cnt; i < cards.size(); i++ ){
        res +=cards[i];
        if( cards[i] & 1 ){
            if( min_odd_sub == -1 )
                min_odd_sub = cards[i];
        }else{
            if( min_even_sub == -1 )
                min_even_sub = cards[i];
        }
    }
    if( (res & 1) == 0 )
        return res;
    for( int i = cards.size() - cnt - 1; i >=0; i-- ){
        if( cards[i] & 1 ){
            if( min_even_sub != -1 )
                return res - min_even_sub + cards[i];
        }else{
            if( min_odd_sub != -1 )
                return res - min_odd_sub + cards[i];
        }
    }
    return 0;
}

