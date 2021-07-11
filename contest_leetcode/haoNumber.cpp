//
// Created by luoxiYun on 2021/7/4.
//

#include <iostream>
using namespace std;
#define MOD 1000000007
/*
 * 这里的快速幂算法由于power很大，需要在运算过程中取余数
 */
long long fast_pow( int n, long long power ){
    long long res = 1, base = n;
    while ( power > 0 ){
        if( power & 1  )
            res = res * base % MOD;
        base = base * base % MOD;
        power >>= 1;
    }
    return res;
}

int countGoodNumber( long long n ){
    long long oddCount = n / 2;
    long long evenCount = ( n+1 )/2;
    if( oddCount == 0 )
        return fast_pow(5, evenCount);
    long long res =  fast_pow(5, evenCount) * fast_pow(4, oddCount) % MOD;
    return res;
}

int main(){
    int n;
    cin>>n;
    while ( n!=-1 ) {
        cout << countGoodNumber(n) << endl;
        cin>>n;
    }
    return 0;
}