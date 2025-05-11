//
// Created by luoxiYun on 2021/3/21.
//

#include "common.h"

class CriticalEdge {
	vector<vector<int>> adj_;
	int nodeCnt;
	vector<int> discover;
	vector<int> low;
	vector<vector<int>> res;

public:
	void dfs(int node, int prev_node) {
		discover[node] = low[node] = nodeCnt++;
		for (int there : adj_[node]) {
			if (there == prev_node) continue;
			if (discover[there] == -1) {
				// cout<<"node:"<<node<<"neighbor:"<<there<<endl;
				dfs(there, node);
				low[node] = min(low[node], low[there]);
				if (low[there] > discover[node]) {
					res.push_back(vector<int>{node, there});
				}
			} else {
				low[node] = min(low[node], low[there]);
			}
		}
	}

	vector<vector<int>> criticalConnections(int n,
	                                        vector<vector<int>>& connections) {
		adj_ = vector<vector<int>>(n);
		for (auto& pair : connections) {
			adj_[pair[0]].push_back(pair[1]);
			adj_[pair[1]].push_back(pair[0]);
		}
		for (int i = 0; i < adj_.size(); i++) cout << adj_[i].size() << endl;
		discover = vector<int>(n, -1);
		low = vector<int>(n, -1);
		for (int i = 0; i < n; i++) {
			if (discover[i] == -1) dfs(i, -1);
		}
		return res;
	}
};

int main() { return 0; }