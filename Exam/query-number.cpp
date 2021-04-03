//
// Created by luoxiYun on 2021/3/27.
//

#include <iostream>
#include <unordered_map>

#define ll long long

using namespace std;

int main(){
    int n, m;
    cin>>n>>m;
    unordered_map<ll, pair<int,int>> table;
    for (int i = 0; i < n; ++i) {
        ll number;
        cin>>number;
        if (table.count(number)==0)
            table[number] = make_pair(i+1, i+1);
        else
            table[number].second = i+1;
    }
    while ( m-- ){
        ll num;
        cin>>num;
        if ( table.count(num) == 0 )
            cout<<0<<endl;
        else
            cout<<table[num].first<<" "<<table[num].second<<endl;
    }
    return 0;
}