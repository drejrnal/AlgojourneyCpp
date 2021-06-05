//
// Created by luoxiYun on 2021/4/18.
//

#ifndef WALKING_LEETCODE_NUMTRIE_H
#define WALKING_LEETCODE_NUMTRIE_H

#define BITINT_MAX 16

#include "common.h"

struct numTrieNode{
    numTrieNode *children[2];
    int value;
    int count; //树中所有元素的前缀经过该节点的个数
    numTrieNode():value(0){
        memset( children, 0, sizeof(children) );
    }
    ~numTrieNode(){
        if (children[0] )
            delete children[0];
        if( children[1] )
            delete children[1];
    }
};

class numTrie{
private:
    numTrieNode *root;
public:
    numTrie(){
        root = new numTrieNode();
    }
    numTrieNode *getRoot(){
        return root;
    }
    bool empty(){
        return root->children[0] == nullptr && root->children[1] == nullptr;
    }
    void insert( int number ){
        numTrieNode *trav = root;
        for( int i = BITINT_MAX - 1; i >= 0; i-- ){
            if( trav->children[(number>>i)&1] == nullptr )
                trav->children[(number>>i)&1] = new numTrieNode();
            trav->count++;
            trav = trav->children[(number>>i)&1];
        }
        trav->value = number;
        trav->count++;
    }
};


#endif //WALKING_LEETCODE_NUMTRIE_H
