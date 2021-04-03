//
// Created by luoxiYun on 2021/3/27.
//

#include "common.h"

class KthMergeUsingPQ{

public:
    vector<int> kthMerge( vector<vector<int>> &nums ){
        vector<int> output;
        vector<int> inPQ( nums.size(), 0 );
        auto comp = [&]( const int i1, const int i2 ){
            return nums[i1][inPQ[i1]] > nums[i2][inPQ[i2]];
        };
        priority_queue<int, vector<int>, decltype(comp)> pq(comp);
        for( int i = 0; i < nums.size(); i++ )
            pq.push( i );
        while( !pq.empty() ){
            int minIndex = pq.top();
            pq.pop();
            output.push_back( nums[minIndex][inPQ[minIndex]] );
            //cout<<nums[minIndex][inPQ[minIndex]]<<" ";
            int nextIndex = ++inPQ[minIndex];
            if ( nextIndex < nums[minIndex].size() )
                pq.push( minIndex );
        }
        return output;
    }
};

int main(){
    vector<vector<int> > arr{ { 2, 6, 12, 23, 45},
                              { 1, 9 },
                              { 23, 34, 90, 2000 } };
    KthMergeUsingPQ kmpq;
    vector<int> res = kmpq.kthMerge(arr);
    cout << "Merged array is " << endl;
    for (auto x : res)
        cout << x << " ";
    return 0;
}