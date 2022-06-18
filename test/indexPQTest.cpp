//
// Created by luoxiYun on 2021/9/8.
//

#include "indexed_priority_queue.h"

void display_index_pq(indexed_priority_queue<int, int> ipq ){
    while ( !ipq.empty() ){
        pair<int, int> ele = ipq.top();
        cout<<ele.first<<"->"<<ele.second<<" at pq["<<ipq.get_value_index(ele.first)<<"]; ";
        ipq.pop();
    }
    cout<<endl;
}

int main(){
    indexed_priority_queue<int, int> ipq;
    ipq.push(2,1);
    ipq.push( 3, 7 );
    ipq.push( 5, 0);
    ipq.push( 4, 5 );
    ipq.push( 1, 3);

    for( int i = 1; i <= 5; i++ )
        cout<<ipq.get_value_index(i)<<" ";
    cout<<endl;
    ipq.changeKey( 4, -2 );
    for( int i = 1; i <= 5; i++ )
        cout<<ipq.get_value_index(i)<<" ";
    cout<<endl;
    display_index_pq( ipq ); //7 3 5 1

    cout<<"size of pq "<<ipq.size()<<endl; //4
    cout<<"Top element: "<<ipq.top().first<<"->"<<ipq.top().second<<endl;//3->7

    ipq.pop();
    ipq.pop();

    cout<<"After poping two elements:"<<endl;
    display_index_pq( ipq );
    cout<<"size of pq "<<ipq.size()<<endl; //2
    cout<<"Top element: "<<ipq.top().first<<"->"<<ipq.top().second<<endl;//1->3

    return 0;
}