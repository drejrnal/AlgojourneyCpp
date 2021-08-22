//
// Created by luoxiYun on 2021/8/21.
//

/*
 * 在你面前有n个蓄水池，他们组成了树形结构（由n-1条边连接）。蓄水池节点编号从1开始到n。
 * 对每个蓄水池节点来说，他的儿子蓄水池节点都摆放在他的下面，并且和它用水管相连，根据重力，水会向下流动。
 * 现在我们要在蓄水池上做一些操作：
 *1. 把节点v填满水。然后v的所有儿子节点水也会被填满
 *2. 清空节点v的水。然后v所有的父亲节点水都会被清空
 *3. 询问每个蓄水池节点是否有水。
 * 初始状态时候，每个节点都是空的。
 * 现在我们会依次进行一系列操作，我们想提前知道每次操作后的结果
 */

#include "common.h"

bool full_of_water[1000];

void tree_down_traverse( vector<vector<int>> &tree, int root ){
    full_of_water[root] = true;
    for( int adj : tree[root] ){
        tree_down_traverse( tree, adj );
    }
}

void tree_up_traverse( vector<int> &parent, int child ){
    while ( child != 0 ){
        full_of_water[child] = false;
        child = parent[child];
    }
    full_of_water[child] = false;
}

int main(){
    int n;
    cin >> n;
    vector< vector<int> > tree( n );
    vector<int> parent(n,-1);
    int here, there;//表示边的两端节点
    for( int i = 0; i < n-1; i++ ){
        cin>>here>>there;
        if( here < there ){
            parent[there-1] = here-1;
            tree[here-1].push_back( there-1 );
        }else{
            parent[here-1] = there-1;
            tree[there-1].push_back( here-1 );
        }
    }
    int query;
    cin >> query;
    int opt, node;
    while ( query-- ){
        cin >> opt >>node;
        switch (opt) {
            case 1:
                tree_down_traverse( tree,node-1 );
                break;
            case 2:
                tree_up_traverse( parent, node-1 );
                break;
            case 3:
                cout<<full_of_water[node-1]<<endl;
                break;
            default:
                break;
        }
    }
    return 0;
}