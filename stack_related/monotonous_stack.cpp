//
// Created by luoxiYun on 2021/9/23.
//

/*
 * 单调栈：用于判断数组中某一位置x
 * 其右侧大于（小于）arr[x]的最近位置；其左侧大于（小于）arr[x]的最近位置
 */

#include <iostream>
#include <stack>
#include <vector>

class MonotonousStack {
public:
    // 找出数组中每个元素右侧第一个大于它的元素的位置
    // 返回一个数组，result[i]表示arr[i]右侧第一个大于arr[i]的元素的位置
    // 如果没有这样的元素，则result[i] = -1
    static std::vector<int> nextGreaterElement(const std::vector<int> &arr) {
        int n = arr.size();
        std::vector<int> result(n, -1);
        std::stack<int> st;  // 存储索引的单调递减栈

        for (int i = 0; i < n; i++) {
            // 当前元素大于栈顶元素，则栈顶元素的下一个更大元素就是当前元素
            while (!st.empty() && arr[i] > arr[st.top()]) {
                result[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }

        return result;
    }

    // 找出数组中每个元素右侧第一个小于它的元素的位置
    static std::vector<int> nextSmallerElement(const std::vector<int> &arr) {
        int n = arr.size();
        std::vector<int> result(n, -1);
        std::stack<int> st;  // 存储索引的单调递增栈

        for (int i = 0; i < n; i++) {
            // 当前元素小于栈顶元素，则栈顶元素的下一个更小元素就是当前元素
            while (!st.empty() && arr[i] < arr[st.top()]) {
                result[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }

        return result;
    }

    // 找出数组中每个元素左侧第一个大于它的元素的位置
    static std::vector<int> prevGreaterElement(const std::vector<int> &arr) {
        int n = arr.size();
        std::vector<int> result(n, -1);
        std::stack<int> st;  // 存储索引的单调递减栈

        for (int i = n - 1; i >= 0; i--) {
            // 当前元素大于栈顶元素，则栈顶元素的左侧第一个更大元素就是当前元素
            while (!st.empty() && arr[i] > arr[st.top()]) {
                result[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }

        return result;
    }

    // 找出数组中每个元素左侧第一个小于它的元素的位置
    static std::vector<int> prevSmallerElement(const std::vector<int> &arr) {
        int n = arr.size();
        std::vector<int> result(n, -1);
        std::stack<int> st;  // 存储索引的单调递增栈

        for (int i = n - 1; i >= 0; i--) {
            // 当前元素小于栈顶元素，则栈顶元素的左侧第一个更小元素就是当前元素
            while (!st.empty() && arr[i] < arr[st.top()]) {
                result[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }

        return result;
    }
};

// 测试函数
void testMonotonousStack() {
    std::vector<int> arr = {3, 7, 1, 4, 2, 5, 8, 6};

    std::cout << "Original array: ";
    for (int num: arr) std::cout << num << " ";
    std::cout << std::endl;

    // 测试右侧第一个大于元素
    std::vector<int> nextGreater = MonotonousStack::nextGreaterElement(arr);
    std::cout << "Next greater element indices: ";
    for (int idx: nextGreater) std::cout << idx << " ";
    std::cout << std::endl;

    // 测试右侧第一个小于元素
    std::vector<int> nextSmaller = MonotonousStack::nextSmallerElement(arr);
    std::cout << "Next smaller element indices: ";
    for (int idx: nextSmaller) std::cout << idx << " ";
    std::cout << std::endl;

    // 测试左侧第一个大于元素
    std::vector<int> prevGreater = MonotonousStack::prevGreaterElement(arr);
    std::cout << "Previous greater element indices: ";
    for (int idx: prevGreater) std::cout << idx << " ";
    std::cout << std::endl;

    // 测试左侧第一个小于元素
    std::vector<int> prevSmaller = MonotonousStack::prevSmallerElement(arr);
    std::cout << "Previous smaller element indices: ";
    for (int idx: prevSmaller) std::cout << idx << " ";
    std::cout << std::endl;
}

int main() {
    testMonotonousStack();
    return 0;
}