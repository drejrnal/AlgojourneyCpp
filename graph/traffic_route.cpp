//
// Created by luoxiYun on 2021/8/1.
//

#include "common.h"

class TrafficRoute {

    unordered_map<int, int> dis;

public:
    /**
     * @param routes routes[i]表示第i辆公交车的路线，routes[i]中的每个元素为站点编号
     * @param source 起始站点
     * @param target 目的地站点
     * @return 从source到target的需要乘坐的最小公交车数量(即使得换乘次数最小)
     * 本题的关键在于如何构建图，然后在该图上进行BFS
     */
    int numBusesToDestination( vector<vector<int>> routes, int source, int target){
        if( source == target )
            return 0;
        unordered_map<int, vector<int>> station_to_bus; //车站到公交车的映射
        unordered_map<int, int> bus_to_transfer; //从始发站所在的公交车开始的换乘次数
        queue<int> buses;
        for( int i = 0; i < routes.size(); i++ ){
            for( int station : routes[i] ){
                if( station == source ) {
                    buses.push(i); //将经过始发站的公交车加入队列中
                    bus_to_transfer[i] = 1;
                }
                station_to_bus[station].push_back( i );
            }
        }
        while( !buses.empty() ){
            int bus = buses.front();
            buses.pop();
            int dist = bus_to_transfer[bus];
            //遍历该公交车所经过的每一站，若正好是终点站，则直接返回；否则，将可从该公交车换乘的公交车添加到队列中，增加换乘次数
            for( int station : routes[bus] ) {
                if (station == target)
                    return dist;
                for( int transfer_bus : station_to_bus[station] ){
                    if( bus_to_transfer.find(transfer_bus) == bus_to_transfer.end() ){
                        bus_to_transfer[transfer_bus] = dist + 1;
                        buses.push(transfer_bus);
                    }
                }
            }
        }
        return -1;
    }
};

int main(){
    TrafficRoute trafficRoute;
    vector<vector<int>> routes = {
            {1,2,7},
            {3,6,7}
    };
    cout<<trafficRoute.numBusesToDestination( routes, 1, 6 )<<endl;
    return 0;
}