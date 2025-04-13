//
// Created by luoxiYun on 2021/3/21.
//

#include "common.h"

class redundantConnection{

    typedef struct disjointSet{
        vector<int> parent;
        //vector<int> size;
        disjointSet(int _size):parent(_size){
            for(int i = 0; i < _size; i++){
                //size[i] = 1;
                parent[i] = i;
            }
        }
        int find(int node){
            return (parent[node] == node) ? node : (parent[node] = find(parent[node]));
        }
        bool merge(int node1, int node2 ){
            int p1 = find(node1), p2 = find(node2);
            if( p1 != p2 ){
                parent[p2] = p1;
                return true;
            }
            return false;
        }
    }DJS;


};