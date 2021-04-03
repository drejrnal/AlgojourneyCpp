//
// Created by luoxiYun on 2021/3/19.
//

#include "common.h"

class kthMinimum{

public:
    int partition( vector<int> &input, int start, int end ){
        int pivot = input[end];
        int left = start;
        for( int i = start; i < end; i++ ){
            if( input[i] <= pivot )
                swap( input[left++], input[i] );
        }
        swap( input[left], input[end] );
        return left;
    }

    vector<int> GetSmallestNumber( vector<int> &input , int k ){
        vector<int> res;
        int start = 0, end = input.size() - 1;
        while( start <= end ){
            int pos = partition( input, start, end );
            if( pos == k - 1 )
                return vector<int>( input.begin(), input.begin()+pos+1 );
            else if ( pos > k - 1 )
                end = pos - 1;
            else
                start = pos + 1;
        }
        return res;
    }

};


int main(){
    kthMinimum kmm;
    vector<int> sample = { 4,5,1,6,2,7,3,8 };
    int k;
    cin>>k;
    vector<int> res = kmm.GetSmallestNumber(sample, k );
    for( int i : res )
        cout<<i<<" ";
    cout<<endl;
    return 0;
}