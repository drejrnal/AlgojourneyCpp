//
// Created by luoxiYun on 2021/4/1.
//

#ifndef WALKING_LEETCODE_TRIE_H
#define WALKING_LEETCODE_TRIE_H

#include "common.h"

#define ALPHABETS 26

struct TrieNode{
    TrieNode *children[ALPHABETS];
    bool isEndOfWord;
    TrieNode():isEndOfWord(false){
        memset( children, 0, sizeof(children) );
    }
    ~TrieNode(){
        for (int i = 0; i < ALPHABETS; ++i) {
            if( children[i] )
                delete children[i];
        }
    }
};

class Trie{
private:
    TrieNode *root;
public:
    Trie(){
        root = new TrieNode();
    }
    inline TrieNode *getRoot(){
        return root;
    }
    void insert( string &key );
    bool search( string &pattern );
    //TODO::添加删除操作
};

#endif //WALKING_LEETCODE_TRIE_H
