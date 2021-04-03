//
// Created by luoxiYun on 2021/3/28.
//
#include "include/common.h"

class Solution3 {
public:
    int reinitializePermutation(int n) {
        vector<int> perm(n);
        for( int i = 0; i < n; i++ )
            perm[i] = i;
        int res= 1;
        vector<int> arr(n);
        while (true) {
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0)
                    arr[i] = perm[i / 2];
                else
                    arr[i] = perm[n / 2 + (i - 1) / 2];
            }
            bool terminate = true;
            for (int i = 0; i < n; ++i) {
                if( arr[i] != i ){
                    terminate = false;
                    break;
                }
            }
            if (terminate )
                break;
            res++;
            swap( perm, arr );
        }
        return res;
    }

};

int main(){
    Solution3 solution3;
    int n = 6;
    cout<<solution3.reinitializePermutation( n )<<endl;
    return 0;
}