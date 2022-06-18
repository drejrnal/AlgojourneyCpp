//
// Created by luoxiYun on 2021/9/20.
//

#include "common.h"

int calculate_string( string &s ){
    int num = 0, prev_res = 0, pos = 0;
    int opt = 1;
    int N = s.length();
    stack<int> st;
    while ( pos < N ){
        if( isdigit(s[pos]) )
            num = num * 10 + s[pos] - '0';
        else if( s[pos] == '+' || s[pos] == '-' ){
            prev_res += opt * num;
            num = 0;
            opt = (s[pos] == '+') ? 1 : -1;
        }
        //遇到左括号 相当于递归调用
        else if( s[pos] == '(' ){
            st.push(prev_res);
            st.push(opt);
            prev_res = 0;
            opt = 1;
        }
        //遇到右括号 相当于一次递归调用完成，返回上一层
        else if( s[pos] == ')' ){
            prev_res +=opt * num;
            int top_opt = st.top();
            st.pop();
            int top_val = st.top();
            st.pop();
            prev_res *=top_opt;
            prev_res +=top_val;
            num = 0;
        }
        pos++;
    }
    int res = ( s[pos-1] == ')' ) ? prev_res : prev_res + opt * num;
    return res;
}

int main(){
    string expression;
    cin>>expression;
    cout<<calculate_string(expression)<<endl;
    return 0;
}