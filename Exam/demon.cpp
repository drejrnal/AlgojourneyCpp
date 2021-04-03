//
// Created by luoxiYun on 2021/3/27.
//

#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main(){
    int n, cost1, cost2;
    cin>>n>>cost1>>cost2;
    string winOrlose;
    cin>>winOrlose;
    stack<char> st;
    int mpCap = 0;
    for (int i = 0; i < n; ++i) {
        if ( winOrlose[i] == 'T' ) {
            while ( !st.empty() )
                st.pop();
        }
        if ( winOrlose[i] == 'F' ){
            if ( st.size() == 2 ){
                mpCap += min(cost1, cost2);
                while (!st.empty() )
                    st.pop();
            }else
                st.push(winOrlose[i]);
        }
    }
    cout<<mpCap<<endl;
}
