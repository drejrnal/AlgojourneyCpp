//
// Created by luoxiYun on 2021/8/14.
//

#include "common.h"

class shortestPath{
    using V = pair<int, int>;
    //邻接表建图
    vector<vector<V>> graph;
public:
    /**
     * 采用dijkstra算法求源点到所有节点的最短路径
     */
     int netWorkDelayTime( vector<vector<int>>& times, int n, int k ){
         graph.resize(n);
         priority_queue<V,vector<V>,greater<> > pq;
         vector<int> distance( n, INT32_MAX );
         for( auto edge : times )
             graph[edge[0]-1].push_back( {edge[1]-1, edge[2]} );
         distance[k-1] = 0;
         pq.push( {k-1, 0} ); //到起始点距离设为0
         while ( !pq.empty() ){
             V entry = pq.top();
             int current = entry.first;
             int cost = entry.second;
             pq.pop();
             for( auto adj_entry : graph[current] ){
                 int next = adj_entry.first;
                 if( distance[next] > cost + adj_entry.second ){
                     distance[next] = cost + adj_entry.second;
                     pq.push( { next, distance[next]} );
                 }
             }
         }
         int res = *max_element( distance.begin(), distance.end() );
         return res != INT32_MAX ? res : -1;
     }
};

int main(){
    shortestPath shortest_path;
    vector<vector<int>> times = {
            {2,1,1},
            {2,3,1},
            {3,4,1}
    };
    cout<<shortest_path.netWorkDelayTime( times, 4, 2 )<<endl;
    return 0;
}