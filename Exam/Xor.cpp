//
// Created by luoxiYun on 2021/3/27.
//

#include <iostream>
#include <vector>

using namespace std;

class Node{

public:
    Node(){}
    Node *next[2]{nullptr, nullptr};

};

class Trie{
private:
    Node *root = nullptr;
public:
    Trie(){
        root = new Node();
    }
    ~Trie(){
        destroyTrie( root );
    }
    void destroyTrie(Node *head){
        if( head != nullptr ){
            if( head->next[0]){
                destroyTrie(head->next[0]);
                head->next[0] = nullptr;
            }
            if( head->next[1]){
                destroyTrie(head->next[1]);
                head->next[1] = nullptr;
            }
        }
    }
    void add(int number){
        Node *trav = root;
        for( int i = 31; i >=0; i-- ){
            int val = ((number >> i) & 1);
            if( trav->next[val] == nullptr )
                trav->next[val] = new Node();
            trav = trav->next[val];
        }
    }
    int maxXor( int number ){
        Node *trav = root;
        int res = 0;
        for( int i = 31; i >=0; i-- ){
            int val = ((number >> i) & 1);
            int best = ( i == 31 )? val:( val ^ 1);
            best = trav->next[best] != nullptr ? best : ( best ^ 1 );
            res |= ( val ^ best )<<i;
            trav = trav->next[best];
        }
        return res;
    }
};

int maxXorSubArray( vector<int> &arr, int k ){
    if( arr.size() == 0 )
        return 0;
    int res = 0;
    for( int i = 0; i < arr.size(); i++ ){
        int eor = 0;
        for( int j = i; j - i < k; j++ ){
            eor = eor ^ arr[j];
            res = max( res, eor );
        }
    }
    return res;
}

int main(){
    int n, k;
    cin>>n>>k;
    vector<int> number;
    for (int i = 0; i < n; ++i) {
        int num;
        cin>>num;
        number.push_back( num );
    }
    for (int i = 0; i < n; ++i) {
        cout<<number[i]<<endl;
    }
    cout<<maxXorSubArray(number,k)<<endl;
    return 0;
}