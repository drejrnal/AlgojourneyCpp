//
// Created by luoxiYun on 2021/3/22.
// 腾讯笔试第5题
//

#include "common.h"

vector<int> backPack01( vector<int> weights, vector<int> &values, int capacity ){
    vector<int> dp( capacity + 1, 0 );
    for( int i = 0; i < weights.size(); i++ ){
        for( int j = capacity; j > 0; j-- ){
            if( j >= weights[i] ){
                dp[j] = max( dp[j], dp[j - weights[i]] + values[i]);
            }
        }
    }
    return dp;
}

int main(){
    int example;
    cin>>example;
    while( example-- ){
        int n,m;
        cin>>n>>m;
        int sum;
        vector<int> price;
        for( int i = 0; i < n; i++ ){
            int ele;
            cin>>ele;
            price.push_back(ele);
        }
        sum = accumulate(price.begin(), price.end(), 0 );
        int capacity = sum / m * m;
        vector<int> shopping = backPack01(price, price, capacity);
        int maxShop;
        cout<<"dp[capacity]:"<<shopping[capacity]<<endl;
        for( auto it = shopping.rbegin(); it != shopping.rend(); it++ ){
            if( *it % m == 0 ){
                maxShop = *it;
                break;
            }
        }
        cout<<" remain: "<<sum - maxShop<<endl;
    }
    return 0;
}