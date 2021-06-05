//
// Created by luoxiYun on 2021/5/30.
//

#include "biIndexTree.h"

int main(){
    vector<int> arr{ 1, 7, 3, 0, 7, 8, 3, 2, 6, 2, 1, 1, 4, 5 };
    biIndexedTree treeArr(arr);
    cout<<treeArr.query( 5 )<<endl; //[0...5]区间和
    treeArr.update( 5, 2 );
    cout<<"After updating:"<<endl;
    cout<<treeArr.query( 5)<<endl;
    treeArr.getTree();

    return 0;
}
