//
// Created by luoxiYun on 2021/4/4.
//

#include "algo_memo.h"


int fast_pow( int base, int power ){
    int res = 1;
    while ( power > 0 ){
        if( power & 1  )
            res *= base;
        base *=base;
        power >>= 1;
    }
    return res;
}
