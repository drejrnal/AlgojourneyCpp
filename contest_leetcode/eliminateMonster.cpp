//
// Created by luoxiYun on 2021/7/4.
//
#include <iostream>
#include <vector>

#define MAX_VAL 100005

using namespace std;

int eliminateMaximum( vector<int>& dist, vector<int>& speed ){
    int n = dist.size();
    vector<double> time( n, 0 );
    for( int i = 0; i < dist.size(); i++ )
        time[i] = double (dist[i]) / speed[i];
    sort( time.begin(), time.end() );
    int ptr = 0, res = 0;
    for( int i = 0; i < n; i++ ){
        if( time[i] > i )
            res++;
        else
            break;
    }
    return res;
}

int main(){
    vector<int> dist = { 4,2,3 };
    vector<int> speed = { 2,1,1 };
    cout<<eliminateMaximum(dist, speed )<<endl;
    return 0;
}