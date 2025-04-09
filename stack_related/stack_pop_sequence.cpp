//
// Created by luoxiYun on 2021/9/7.
//

#include "common.h"
/*
 * 给定一个序列，该序列按顺序进栈（其间穿插着出栈操作），求所有可能的出栈序列(按字典序顺序输出)
 * 本题另一种类型是：给定进栈序列和出栈序列，判断该出栈序列是否合法
 */
class stackPopSequence {
private:
    set<vector<int>> results;
public:
    void enumerate_sequences(vector<int> &origin, stack<int> &st, vector<int> &on_fly, int stack_index) {
        if (on_fly.size() == origin.size() && stack_index == origin.size()) {
            results.insert(on_fly);
            return;
        }
        //递归第一种情况：当前stack_index位置的元素进栈
        if (stack_index < origin.size()) {
            st.push(origin[stack_index]);
            enumerate_sequences(origin, st, on_fly, stack_index + 1);
            st.pop();
        }
        //递归第二种情况：当前stack_index位置元素暂不进栈，从栈顶取一元素后，在递归到第一种情况
        if (!st.empty()) {
            int top = st.top();
            st.pop();
            on_fly.push_back(top);
            enumerate_sequences(origin, st, on_fly, stack_index);
            on_fly.pop_back();
            st.push(top);
        }
        return;
    }
    /*
     * getter method
     */
    set<vector<int>> getEnumSequence() {
        return results;
    }
};

int main(){
    int size;
    cin>>size;
    vector<int> origins;
    origins.resize(size);
    for( int i = 0; i < size; i++ )
        cin>>origins[i];
    stack<int> st;
    vector<int> fly;
    stackPopSequence pop;
    pop.enumerate_sequences(origins, st, fly, 0);
    set<vector<int>> results = pop.getEnumSequence();
    vector<vector<int>> output(results.size());
    for (const vector<int> &seq: results) {
        for (int num: seq) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}