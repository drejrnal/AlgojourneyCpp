//
// Created by luoxiYun on 2021/9/8.
//

#ifndef WALKING_LEETCODE_INDEXED_PRIORITY_QUEUE_H
#define WALKING_LEETCODE_INDEXED_PRIORITY_QUEUE_H

#include "common.h"
/*
 * 二叉堆
 * 拓展priority_queue<T>，多了changeKey(Key, Value)接口
 */
template<class Key, class Value, class Comparator = less<Value>,
        class Hash = hash<Key>>
class indexed_priority_queue {
private:
    vector<pair<Key, Value>> pq;  //根据优先级顺序存放的元素，符合完全二叉树
    unordered_map<Key, int> position;  // value是key在pq内的下标位置
    Comparator comparator;             //优先级比较器
    int numOfElements;                 //当前pq的元素个数
    /*
     * helper function
     */
    //堆的向上调整
    void swim(int first, int topIndex, int holeIndex) {
        int parentIndex = (holeIndex - 1) / 2;
        while (holeIndex > topIndex &&
               comparator(pq[first + parentIndex].second,
                          pq[first + holeIndex].second)) {
            std::swap(pq[first + parentIndex], pq[first + holeIndex]);
            position[pq[first + parentIndex].first] = first + parentIndex + 1;
            position[pq[first + holeIndex].first] = first + holeIndex + 1;
            holeIndex = parentIndex;
            parentIndex = (holeIndex - 1) / 2;
        }
    }

    //堆的向下调整
    void sink(int first, int len, int holeIndex) {
        while ((2 * holeIndex + 1) < len) {
            int child = 2 * holeIndex + 1;
            if (child + 1 < len && comparator(pq[first + child].second,
                                              pq[first + child + 1].second))
                child = child + 1;
            if (!comparator(pq[first + holeIndex].second,
                            pq[first + child].second))
                break;
            swap(pq[first + holeIndex], pq[first + child]);
            position[pq[first + holeIndex].first] = first + holeIndex + 1;
            position[pq[first + child].first] = first + child + 1;
            holeIndex = child;
        }
    }

public:
    indexed_priority_queue() { numOfElements = 0; }

    indexed_priority_queue(Comparator comparator1) {
        numOfElements = 0;
        this->comparator = comparator1;
    }

    pair<Key, Value> top() { return pq[0]; }

    int size() { return numOfElements; }

    bool empty() { return numOfElements == 0; }

    int get_value_index(Key key) {
        if (!position.contains(key)) {
            return -1;
        }
        return position[key] - 1;
    }

    //添加元素，要求不能重复添加
    void push(Key key, Value val) {
        if (position.contains(key)) {
            cout << " key already exist " << endl;
            return;
        }
        pq.push_back({key, val});
        numOfElements++;
        position[key] = numOfElements;
        swim(0, 0, numOfElements - 1);
    }

    //如果堆顶元素需要删除，则删除堆顶元素
    void pop() {
        std::swap(pq[0], pq[numOfElements - 1]);
        position[pq[0].first] = 1;
        pq.pop_back();
        position.erase(pq[numOfElements - 1].first);
        sink(0, numOfElements - 1, 0);

        numOfElements--;
    }

    // Remove an element by its key
    void remove(Key key) {
        if (!position.contains(key)) {
            cout << "key does not exist" << endl;
            return;
        }

        int index = position[key] - 1;

        // If it's the last element, just remove it
        if (index == numOfElements - 1) {
            pq.pop_back();
            position.erase(key);
            numOfElements--;
            return;
        }

        // Swap with the last element
        std::swap(pq[index], pq[numOfElements - 1]);
        position[pq[index].first] = index + 1;

        // Remove the last element (original element at index)
        pq.pop_back();
        position.erase(key);
        numOfElements--;

        // Restore heap property
        sink(0, numOfElements, index);
        swim(0, 0, index);
    }

    void changeKey(Key key, Value val) {
        if (!position.contains(key)) {
            cout << "no key exist" << endl;
            return;
        }
        int index = position[key] - 1;
        pq[index] = {key, val};
        sink(0, numOfElements, index);
        swim(0, 0, index);
    }
};

#endif  // WALKING_LEETCODE_INDEXED_PRIORITY_QUEUE_H