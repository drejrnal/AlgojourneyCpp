//
// Created by luoxiYun on 2021/8/14.
//

#include "common.h"

class shortestPath {
    using V = pair<int, int>;
    using PR = pair<int, pair<int, int>>;
    //邻接表建图
    vector<vector<V>> graph;
public:
    /**
     * 采用dijkstra算法求源点到所有节点的最短路径
     */
    int netWorkDelayTime(vector<vector<int>> &times, int n, int k) {
        graph.resize(n);
        priority_queue<V, vector<V>, greater<> > pq;
        vector<int> distance(n, INT32_MAX);
        for (auto edge : times)
            graph[edge[0] - 1].push_back({edge[1] - 1, edge[2]});
        distance[k - 1] = 0;
        pq.push({k - 1, 0}); //到起始点距离设为0
        while (!pq.empty()) {
            V entry = pq.top();
            int current = entry.second;
            int cost = entry.first;
            pq.pop();
            for (auto adj_entry : graph[current]) {
                int next = adj_entry.first;
                if (distance[next] > cost + adj_entry.second) {
                    distance[next] = cost + adj_entry.second;
                    pq.push({distance[next], next});
                }
            }
        }
        int res = *max_element(distance.begin(), distance.end());
        return res != INT32_MAX ? res : -1;
    }
    /*
     * 力扣题目 1928
     */
    int minCost( int max_time, vector<vector<int>> &edges, vector<int> &passing_fees ){
        int n = passing_fees.size();
        vector<vector<int>> dp(  n, vector<int>(max_time+1, INT32_MAX ));
        graph.resize( n );
        for( auto &edge : edges ) {
            graph[edge[0]].push_back({edge[1], edge[2]});
            graph[edge[1]].push_back( {edge[0], edge[2]} );
        }
        dp[0][0] = passing_fees[0];
        for( int time = 1; time <= max_time; time++ ) {
            for (int here = 0; here < n; here++) {
                for (int i = 0; i < graph[here].size(); i++) {
                    int adj = graph[here][i].first;
                    int time_consume = graph[here][i].second;
                    if( time >= time_consume && dp[here][time - time_consume] != INT32_MAX)
                        dp[adj][time] = min(dp[here][time - time_consume] + passing_fees[adj], dp[adj][time]);
                }
            }
        }
        int res = *min_element( dp[n-1].begin(), dp[n-1].end() );
        return res == INT32_MAX ? -1 : res;
    }


    /*
     * 力扣题目 787
     */
    int shortestDistanceWithinKstops(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        graph.resize(n);
        priority_queue<PR, vector<PR>, greater<> > pq;
        vector<vector<int>> distance(n, vector<int>(k + 2, INT32_MAX));
        for (auto edge : flights)
            graph[edge[0]].push_back({edge[1], edge[2]});
        distance[src][k + 1] = 0;
        pq.push({0, {src, k + 1}}); //到起始点距离设为0
        while (pq.empty()) {
            PR entry = pq.top();
            int stop_remaining = entry.second.second;
            int current = entry.second.first;
            int cost = entry.first;
            pq.pop();
            for (auto adj_entry : graph[current]) {
                int next = adj_entry.first;
                int price = adj_entry.second;
                if (stop_remaining >= 1 && distance[next][stop_remaining - 1] > cost + price) {
                    distance[next][stop_remaining - 1] = cost + price;
                    pq.push({distance[next][stop_remaining - 1], {next, stop_remaining - 1}});
                }
            }
        }
        int min_dis = *min_element(distance[dst].begin(), distance[dst].end());
        return min_dis == INT32_MAX ? -1 : min_dis;
    }
    int distanceWithinKstops(int n, vector<vector<int>> &flights, int src, int dst, int k){
        graph.resize( n );
        vector<int> distance(n, INT32_MAX);
        int stop = 0;
        for (auto edge : flights)
            graph[edge[0]].push_back({edge[1], edge[2]});
        distance[src] = 0;
        queue<int> q;
        q.push(src);
        while( stop < k && !q.empty() ){
            int cur_size = q.size();
            for( int i = 0; i < cur_size; i++ ){
                int top = q.front();
                q.pop();
                for( auto &adj : graph[top] ){
                    if(distance[adj[0]] > adj[1] + distance[top] ){
                        distance[adj[0]] = adj[1] + distance[top];
                        if( distance[adj[0]] >= distance[dst] )
                            q.push(adj[0]);
                    }
                }
            }
        }
        return distance[dst] == INT32_MAX ? -1 : distance[dst];
    }

};

int main() {
    shortestPath shortest_path;
    vector<vector<int>> times = {
            {0, 1, 10},
            {1, 2, 10},
            {2, 5, 10},
            {0, 3, 1},
            {3, 4, 10},
            {4, 5, 15}
    };
    int maxtime = 29;
    vector<int> fees = { 5,1,2,20,20,3 };
    //cout << shortest_path.netWorkDelayTime(times, 4, 2) << endl;
    cout<<shortest_path.minCost(maxtime, times, fees )<<endl;
    return 0;
}