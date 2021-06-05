//
// Created by luoxiYun on 2021/4/4.
//

#include "algo_memo.h"

int integerBreak( int n ){
    int divisorEqualThree = n / 3, remaining = n % 3;
    int res = fast_pow( 3, divisorEqualThree ) * (remaining == 0 ? 1: remaining);
    int multiplier = fast_pow( 3, divisorEqualThree - 1 );
    res = max(res, multiplier * (remaining+3));
    return res;
}

