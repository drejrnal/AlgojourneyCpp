//
// Created by luoxiYun on 2021/3/15.
//

#include "common.h"

class MedianFinder{

    priority_queue<int> maxPQ;
    priority_queue<int, vector<int>, greater<int>> minPQ;
public:

    MedianFinder(){

    }
    void addNumber( int number ){
        if( !minPQ.empty() && (number >= minPQ.top()) )
            minPQ.push( number );
        else
            maxPQ.push( number );
        int l = maxPQ.size(), r = minPQ.size();
        if( l - r > 1 ){
            int maxTop = maxPQ.top();
            maxPQ.pop();
            minPQ.push( maxTop );
        }else if( r - l > 1 ){
            int minTop = minPQ.top();
            minPQ.pop();
            maxPQ.push( minTop );
        }
    }
    double getMedian(){
        if( maxPQ.size() == minPQ.size() )
            return (double)( maxPQ.top() + minPQ.top() )/2;
        else
            return maxPQ.size() > minPQ.size() ? maxPQ.top() : minPQ.top();
    }

};
/*
int main(){
    int num;
    MedianFinder medianFinder;
    vector<int> nums = { 1, 2, 3, 4, 5 };
    for(int num : nums ){
        medianFinder.addNumber( num );

            cout<<medianFinder.getMedian()<<endl;
    }
    return 0;
}*/