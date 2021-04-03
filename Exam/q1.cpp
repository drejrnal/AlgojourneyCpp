//
// Created by luoxiYun on 2021/3/12.
//

#include "include/common.h"
#include <queue>

#define MAX_NODE 100
typedef long long ll;

vector<int> dist(MAX_NODE, -1);

int bfs( vector<vector<int>> &graph, int s, int target ){

    queue<int> q;
    dist[s] = 0;
    q.push( s );
    while( !q.empty() ){
        int t = q.front();
        q.pop();
        for( int adj : graph[t] ){
            if( adj == target ) {
                dist[adj] = dist[t] + 1;
                return dist[adj];
            }
            if( dist[adj] == -1 ) {
                dist[adj] = dist[t] +1;
                q.push(adj);
            }
        }
    }
    return -1;
}

int main(){
    int number, relation;

    cin>>number>>relation;
    vector<vector<int>> graph(number+1);
    vector<vector<ll>> distance( number+1, vector<ll>(number+1, INT32_MAX));
    while( relation-- ){
        int n1, n2;
        cin>>n1>>n2;
        distance[n1][n2] = 1;
    }

    for( int k = 1; k <= number; k++){
        for( int i = 1; i <=number; i++){
            for( int j = 1; j <= number; j++ ){
                distance[i][j] = min(distance[i][j], distance[i][k]+distance[k][j]);
            }
        }
    }

    int query;
    cin>>query;
    while ( query-- ){
        int begin, end;
        cin>>begin>>end;
        if ( distance[begin][end] >= INT32_MAX )
            cout<<-1<<endl;
        else
            cout<<distance[begin][end]<<endl;
    }
    return 0;
}