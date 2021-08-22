//
// Created by luoxiYun on 2021/5/30.
//

#ifndef WALKING_LEETCODE_BIINDEXTREE_H
#define WALKING_LEETCODE_BIINDEXTREE_H
/*
 * binary indexed tree 树状数组
 */
#include "common.h"

class biIndexedTree{

    vector<int> tree; //tree[i]表示区间树中以arr[i-1]为右端点节点保存的信息

public:
    biIndexedTree( int size ){
        tree.resize(size);
        for( int i = 0; i < size; i++ ){
            tree[i] = 0;
        }
    }
    biIndexedTree( vector<int> &arr ){
        tree.resize( arr.size() + 1 );
        for( int i = 1; i < tree.size(); i++ ){
            tree[i] = arr[i-1];
        }
        for( int i = 1; i < tree.size(); i++ ){
            int j = i + ( i & (-i) );
            if( j < tree.size() ) tree[j] +=tree[i];
        }
    }
    /*
     * 查询[0...pos]区间的区间和
     *  O(lgN)复杂度，因为涉及lgN个区间
     */
    int query( int pos ){
        pos +=1;
        int result = 0;
        while( pos > 0 ){
            result +=tree[pos];
            pos -=( pos & (-pos) );
        }
        return result;
    }
    /*
     * 更新arr[pos]的值，相应的更新所有包含arr[pos]区间的信息
     */
    void update( int pos, int addition ){
        pos +=1;
        while( pos < tree.size() ){
            tree[pos] +=addition;
            pos +=( pos & (-pos) );
        }
    }
    void getTree(){
        for( int i = 1; i < tree.size(); i++ )
            cout<<"["<<i<<"]"<<tree[i]<<" ";
        cout<<endl;
    }

};

#endif //WALKING_LEETCODE_BIINDEXTREE_H
