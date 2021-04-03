//
// Created by luoxiYun on 2021/3/22.
// 腾讯笔试第3题
//

#include "include/common.h"

int main(){
    int num;
    cin>>num;
    vector<vector<int>> input(num);
    for( int i = 0; i < num; i++ ){
        int size;
        cin>>size;
        vector<int> arr(size);
        int ele;
        for (int j = 0; j < size; ++j) {
            cin>>ele;
            arr[j] = ele;
        }
        sort( arr.begin(), arr.end() );
        input[i] = arr;
    }
   // kthMinimum kmm;

    int query;
    cin>>query;
    while( query-- ){
        int mergeCnt;
        cin>>mergeCnt;
        vector<int> inPQ( num, 0 );
        auto comp = [&]( const int i1, const int i2 ){
            return input[i1][inPQ[i1]] > input[i2][inPQ[i2]];
        };
        int index;
        priority_queue<int, vector<int>, decltype(comp)> pq(comp);
        for( int i = 0; i < mergeCnt; i++ ) {
            cin>>index;
            pq.push(index);
        }
        int k; cin>>k; int tmp = 0;
        while( !pq.empty() && tmp < k ){
            int minIndex = pq.top();
            pq.pop();
            cout<<input[minIndex][inPQ[minIndex]]<<" ";
            tmp++;
            int nextIndex = ++inPQ[minIndex];
            if ( nextIndex < input[minIndex].size() )
                pq.push( minIndex );
        }
        cout<<endl;
    }
    return 0;
}