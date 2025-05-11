//
// Created by yixin on 25-5-8.
//

#include <deque>
#include <optional>
#include <iostream>
using namespace std;

class MinStack {
private:
    deque<int> stack;
    deque<int> min_stack;

public:
    MinStack(){
    }
    bool isEmpty(){
        return stack.empty();
    }
    void push(int x) {
        stack.push_back(x);
        if(min_stack.empty() || min_stack.back() >= x){
            min_stack.push_back(x);
        }
    }
    optional<int> pop() {
        if(stack.empty()){
            cout << "Stack is empty, cannot pop." << endl;
            return nullopt;  // Indicate null value
        }
        int x = stack.back();
        stack.pop_back();
        if(x == min_stack.back()){
            min_stack.pop_back();
        }
        return x;
    }
    optional<int> getMin(){
        if (min_stack.empty()){
            cout << "Stack is empty, no minimum value." << endl;
            return nullopt;  // Indicate null value
        }
        return min_stack.back();
    }
};

int main(){
    MinStack s;
    cout << "Stack is empty: " << (s.isEmpty() ? "true" : "false") << endl;
    
    cout << "\nPushing 5..." << endl;
    s.push(5);
    cout << "Min: " << s.getMin().value()  << endl;  // Expected: 5
    
    cout << "\nPushing 3..." << endl;
    s.push(3);
    cout << "Min: " << s.getMin().value() << endl;  // Expected: 3
    
    cout << "\nPushing 7..." << endl;
    s.push(7);
    cout << "Min: " << s.getMin().value() << endl;  // Expected: 3
    
    cout << "\nPushing 2..." << endl;
    s.push(2);
    cout << "Min: " << s.getMin().value() << endl;  // Expected: 2
    
    cout << "\nPushing 2 again..." << endl;
    s.push(2);  // Duplicate minimum
    cout << "Min: " << s.getMin().value() << endl;  // Expected: 2

    auto pop_res = s.pop();
    while (pop_res.has_value()) {
        cout << "\nPopping " << pop_res.value() << "..." << endl;  // Pops 2
        if(s.getMin().has_value()) {
            cout << "Min after pop: " << s.getMin().value() << endl;  // Expected: 2 (still)
        }
        pop_res = s.pop();
    }

    // Edge case: operations on empty stack
    cout << "\nTrying operations on empty stack:" << endl;
    s.getMin();

    cout << "Pop: ";
    s.pop();
    
    return 0;
}