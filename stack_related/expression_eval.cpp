//
// Created by luoxiYun on 2021/9/20.
//

#include "common.h"

/**
 * calculate string representative expression
 * the expression will contain parenthesis
 * @param s
 * @return
 */
int calculate_parenthesis_expression(string &s) {
    int num = 0, prev_res = 0, pos = 0;
    int opt = 1;
    int N = s.length();
    stack<int> st;
    while (pos < N) {
        if (isdigit(s[pos]))
            num = num * 10 + s[pos] - '0';
        else if (s[pos] == '+' || s[pos] == '-') {
            prev_res += opt * num;
            num = 0;
            opt = (s[pos] == '+') ? 1 : -1;
        }
            //遇到左括号 相当于递归调用
        else if (s[pos] == '(') {
            st.push(prev_res);
            st.push(opt);
            prev_res = 0;
            opt = 1;
        }
            //遇到右括号 相当于一次递归调用完成，返回上一层
        else if (s[pos] == ')') {
            prev_res += opt * num;
            int top_opt = st.top();
            st.pop();
            int top_val = st.top();
            st.pop();
            prev_res *= top_opt;
            prev_res += top_val;
            num = 0;
        }
        pos++;
    }
    int res = (s[pos - 1] == ')') ? prev_res : prev_res + opt * num;
    return res;
}

/**
 * @return
 */
int calculate_string(string &s) {
    unsigned int num = 0;
    deque<char> oprand;
    deque<unsigned int> op_value;
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) {
            num = (num * 10 + s[i] - '0');
        } else if (s[i] == '+' || s[i] == '-') {
            oprand.push_back(s[i]);
            op_value.push_back(num);
            num = 0;
        } else if (s[i] == '*' || s[i] == '/') {
            char opt = s[i];
            int j = i + 1;
            unsigned int front_num = 0;
            while (j < s.length()) {
                if (isdigit(s[j])) {
                    front_num = (front_num * 10 + s[j] - '0');
                    j++;
                } else if (isblank(s[j])) {
                    j++;
                } else {
                    break;
                }
            }
            num = (opt == '*') ? (num * front_num) : (num / front_num);
            i = j - 1;
        } else if (isblank(s[i])) {
            continue;
        }
    }
    op_value.push_back(num);
    unsigned int result = op_value.front();
    op_value.pop_front();
    while (!op_value.empty()) {
        char opt = oprand.front();
        oprand.pop_front();
        result = (opt == '+') ? (result + op_value.front()) : (result - op_value.front());
        op_value.pop_front();
    }
    return result;
}

string compress(string str, int &begin);

/**
 * when begin point to a '[', eval the string in the bracket
 * @param str
 * @param begin
 * @return
 */
string eval_bracket(const string &str, int &begin) {
    string eval = "";
    //先获取num
    begin++; //skip '['
    int temp_ptr = begin;
    while (str[temp_ptr] <= '9' && str[temp_ptr] >= '0')
        temp_ptr++;
    int freq = stoi(str.substr(begin, temp_ptr - begin));
    begin = temp_ptr + 1; //skip '|'
    string sub = compress(str, begin);
    for (int i = 0; i < freq; i++)
        eval += sub;
    begin++; //skip ']'
    return eval;
}

string compress(const string str, int &trav) {
    // write code here
    int n = str.length();
    string res = "";
    while (trav < n) {
        if (str[trav] == '[') {
            string bracket = eval_bracket(str, trav);
            res += bracket;
        } else if (str[trav] == ']') {
            break;
        } else {
            //此时，遍历到的一定是字符,将此字符所在位置到下一个'['之间的子串添加到res中。
            int temp_ptr = trav;
            while (isalpha(str[temp_ptr])) {
                temp_ptr++;
            }
            string partial(str.substr(trav, temp_ptr - trav));
            trav = temp_ptr;
            res += partial;
        }
    }
    return res;
}

string compress(string &str) {
    int trav = 0;
    return compress(str, trav);
}

/**
 * caluculate string expression which contain number and operator +, -, *, / no parenthesis
 * use stack to implement this, not deque. note that +, - is left associative how to do this using stack
 * @return
 */

int main() {
    //string expression;
    //getline(cin, expression);
    //cout<<calculate_parenthesis_expression(expression)<<endl;
    //cout << calculate_string(expression) << endl;
    string compressive = "[3|ab]";
    string res = compress(compressive);
    cout << res << endl;
    return 0;
}