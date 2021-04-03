//
// Created by luoxiYun on 2021/4/1.
//

#include "Trie.h"

void Trie::insert(string &key) {

    struct TrieNode *trav = root;
    for( int i = 0; i < key.length(); i++ ){
        int pos = key[i] - 'a';
        if( trav->children[pos] == nullptr )
            trav->children[pos] = new TrieNode();
        trav = trav->children[pos];
    }
    trav->isEndOfWord = true;

}

bool Trie::search(string &pattern) {

    struct TrieNode *trav = root;
    for( int i = 0; i < pattern.length(); i++ ){
        int pos = pattern[i] - 'a';
        if( trav->children[pos] == nullptr )
            return false;
        trav = trav->children[pos];
    }
    return trav != nullptr && trav->isEndOfWord;

}

