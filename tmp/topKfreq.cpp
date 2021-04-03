//
// Created by luoxiYun on 2021/3/13.
//

#include "include/common.h"
#include <queue>

class topKFreq{

public:
    vector<vector<string>> topKStrings( vector<string> &strings, int k ){
        map<string, int> table;
        vector<vector<string>> result;
        for( string ele : strings ){
            table[ele] +=1;
        }
        auto comp = []( const pair<string, int> &left, const pair<string, int> &right ){
            if( left.second != right.second )
                return left.second > right.second;
            else
                return left.first < right.first;

        };
        priority_queue< pair<string, int>, vector<pair<string, int>>, decltype(comp)> pq(comp);
        for( auto val : table ){
            if( pq .size() < k )
                pq.push(val);
            else{
                pair<string, int> top = pq.top();
                if( comp(val, top) ){
                    pq.pop();
                    pq.push(val);
                }
            }
        }
        while( !pq.empty() ){
            auto top = pq.top();
            pq.pop();
            result.push_back(vector<string>{ top.first, to_string(top.second) } ) ;
        }
        reverse( result.begin(), result.end() );
        return result;
    }
};
int main(){
    topKFreq tkf;
    vector<string> args1 = { "1","2","3","4" };
    int k = 2;
    auto res = tkf.topKStrings(args1, 2);
    for( auto ele : res ){
        cout<<ele[0]<<" "<<ele[1]<<endl;
    }
    return 0;
}