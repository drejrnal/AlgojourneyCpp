//
// Created by luoxiYun on 2021/3/18.
//

#include "common.h"

class Topology {

    bool cycle = false;

public:
    void dfs(vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &onstack, int node) {
        visited[node] = true;
        onstack[node] = true;
        for (int adj : graph[node]) {
            if (!visited[adj]) {
                visited[adj] = true;
                dfs(graph, visited, onstack, adj);
            } else if (onstack[adj]) {
                cycle = true;
                break;
            }
        }
        onstack[node] = false;
    }
    //判断图中是否有环，如果遇到环，则结束当前节点dfs的过程，color[node] = 1表明node节点在栈中。
    bool has_loop_on_dfs( vector<vector<int>> &graph, vector<int> &color, int start ){
        if( color[start] > 0 )
            return color[start] == 1;
        color[start] = 1;
        for( int adjacent : graph[start] ){
            if(has_loop_on_dfs(graph, color, adjacent)){
                return true;
            }
        }
        color[start] = 2;
    }
    //执行完该方法后 可判断图中哪些节点是环上节点，哪些不是。
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> color( graph.size(), 0 );
        vector<int> res;
        for( int i = 0; i < graph.size(); i++ ){
            if( has_loop_on_dfs(graph,color,i) )
                continue;
            res.push_back(i);
        }
        return res;
    }
    /*
     * 注意广度优先搜索一定要注意起始点不同，运算的结果也会不同
     */
    bool bfs(vector<int> &inEdge, vector<vector<int>> &graph) {
        queue<int> q;
        for (int i = 0; i < inEdge.size(); i++)
            if (inEdge[i] == 0)
                q.push(i);
        int visit = 0;
        while (!q.empty()) {
            visit++;
            int top = q.front();
            q.pop();
            for (int adj : graph[top]) {
                if (--inEdge[adj] == 0)
                    q.push(adj);
            }
        }
        return visit == inEdge.size();
    }



    //prerequisites[i][1]->prerequisites[i][0]
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inEdge(numCourses, 0);

        for (auto &ele : prerequisites) {
            graph[ele[1]].push_back(ele[0]);
            inEdge[ele[0]]++;
        }
        //vector<bool> visited( numCourses, false );
        //vector<bool> onStack( numCourses, false);

        return bfs(inEdge, graph);
    }

};
/*
int main() {
    int numCourses = 5;
    vector<vector<int>> pre = {
            {1, 4},
            {2, 4},
            {3, 1},
            {3, 2}
    };
    Topology topology;
    cout << topology.canFinish(numCourses, pre) << endl;
    return 0;
}
 */