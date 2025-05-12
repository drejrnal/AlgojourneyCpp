//
// Created by luoxiYun on 2021/8/1.
//

#include "common.h"

struct StationNode {
    int station;
    int route_num;

    StationNode(int station, int route_num)
            : station(station), route_num(route_num) {}

    bool operator==(const StationNode &other) const {
        return station == other.station && route_num == other.route_num;
    }
};

namespace std {
    template<>
    struct hash<StationNode> {
        size_t operator()(const StationNode &node) const {
            return hash<int>()(node.station) ^ hash<int>()(node.route_num);
        }
    };
}  // namespace std

class TrafficRoute {
private:
    int target_route;
    vector<StationNode> path;
public:

    /**
     * 题目815 公交路线
     * @param routes
     * routes[i]表示第i辆公交车的路线，routes[i]中的每个元素为站点编号
     * @param source 起始站点
     * @param target 目的地站点
     * @return 从source到target的需要乘坐的最小公交车数量(即使得换乘次数最小)
     * 本题的关键在于如何构建图，然后在该图上进行BFS
     */
    int numBusesToDestination(vector<vector<int>> routes, int source,
                              int target) {
        if (source == target) return 0;
        unordered_map<int, vector<int>> station_to_bus;  //车站到公交车的映射
        unordered_map<int, int>
                bus_to_transfer;  //从始发站所在的公交车开始的换乘次数
        queue<int> buses;
        //path[i]表示<从哪一条线路,哪一个站点>换乘到线路i
        path.resize(routes.size(), StationNode(-1, -1));
        for (int i = 0; i < routes.size(); i++) {
            for (int station: routes[i]) {
                if (station == source) {
                    buses.push(i);  //将经过始发站的公交车加入队列中
                    bus_to_transfer[i] = 1;
                }
                station_to_bus[station].push_back(i);
            }
        }
        while (!buses.empty()) {
            int bus = buses.front();
            buses.pop();
            int dist = bus_to_transfer[bus];
            //遍历该公交车所经过的每一站，若正好是终点站，则直接返回；否则，将可从该公交车换乘的公交车添加到队列中，增加换乘次数
            for (int station: routes[bus]) {
                if (station == target) {
                    target_route = bus;
                    return dist;
                }
                for (int transfer_bus: station_to_bus[station]) {
                    if (bus_to_transfer.find(transfer_bus) ==
                        bus_to_transfer.end()) {
                        bus_to_transfer[transfer_bus] = dist + 1;
                        buses.push(transfer_bus);
                        path[transfer_bus] = StationNode(station, bus);
                    }
                }
            }
        }
        return -1;
    }

    vector<vector<int>> getPath(vector<vector<int>> routes, int source, int target) {
        int dist = numBusesToDestination(routes, source, target);
        if (dist == -1) return {};
        unordered_map<StationNode, vector<StationNode>> graph;
        for (int i = 0; i < routes.size(); i++) {
            StationNode traverse_station = StationNode(routes[i][0], i);
            for (int j = 1; j < routes[i].size(); j++) {
                StationNode next_station = StationNode(routes[i][j], i);
                graph[traverse_station].push_back(next_station);
                traverse_station = next_station;
            }
            graph[traverse_station].push_back(StationNode(routes[i][0], i));
        }
        int curr_bus = target_route;
        int target_station = target;
        deque<vector<int>> path_queue;
        while (curr_bus != -1) {
            vector<int> path_within_route;
            StationNode prev_node = path[curr_bus];
            int traverse_station = prev_node.station == -1 ? source : prev_node.station;
            int traverse_station_index = 0;
            for (int i = 0; i < routes[curr_bus].size(); i++) {
                if (routes[curr_bus][i] == traverse_station) {
                    traverse_station_index = i;
                    break;
                }
            }
            while (traverse_station != target_station) {
                int next_station = routes[curr_bus][traverse_station_index];
                path_within_route.push_back(next_station);
                traverse_station_index = (traverse_station_index + 1) % routes[curr_bus].size();
                traverse_station = next_station;
            }
            path_queue.push_front(path_within_route);
            curr_bus = prev_node.route_num;
            target_station = prev_node.station;
        }
        vector<vector<int>> result;
        while (!path_queue.empty()) {
            result.push_back(path_queue.front());
            path_queue.pop_front();
        }
        return result;
    }

};

int main() {
    TrafficRoute trafficRoute;
    vector<vector<int>> routes = {
            {1,  9,  12, 20, 23, 24, 35, 38},
            {10, 21, 24, 31, 32, 34, 37, 38, 43},
            {10, 19, 28, 37},
            {8},
            {14, 19},
            {11, 17, 23, 31, 41, 43, 44},
            {21, 26, 29, 33},
            {5,  11, 33, 41},
            {4,  5,  8,  9,  24, 44}
    };
    cout << trafficRoute.numBusesToDestination(routes, 37, 28) << endl;
    vector<vector<int>> path = trafficRoute.getPath(routes, 37, 28);
    for (auto p: path) {
        for (auto station: p) {
            cout << station << " ";
        }
        cout << endl;
    }
    return 0;
}