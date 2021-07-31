//
// Created by luoxiYun on 2021/7/27.
//

/**
 * 需要考虑1.随着数据流内的元素不断增加，最小k个数和最大k个数的集合也是动态变化的。
 *        2. 因为需要求m个数的平均值，当流内元素大于m时，最小k个数和最大k个数的集合也是动态变化的。
 */
#include "common.h"

class MKAverage {
    int m_, k_;
    queue<int> numberStream; //记录后m个数
    multiset<int> minKset;
    multiset<int> maxKset;
    multiset<int> availableNum;
    //sum表示availableNum集合内的元素和，实时更新
    int sum;
public:
    MKAverage(int m, int k):m_(m), k_(k) {
        sum = 0;
    }
    /*
     * 查找最小k个数集合（最大k个数集合）的最大值（最小值），插入元素时，判断该元素是否应插入到上述集合中
     */
    void addElement(int num) {
        if( numberStream.size() < k_ ){
            minKset.insert( num );
        }else if( numberStream.size() < 2 * k_ ){
            int maxInMinKset = *( minKset.rbegin() );
            if( num >= maxInMinKset )
                maxKset.insert(num);
            else {
                minKset.erase( prev(minKset.end()) );//从最小k集合中删除最大值
                minKset.insert( num );
                maxKset.insert( maxInMinKset );
            }
        }else {
            //如果这时队列中的元素已经有m个元素了，则新添加元素时，考虑队列中元素过期的情形。
            if (numberStream.size() == m_) {
                int evicted = numberStream.front();
                numberStream.pop();
                auto iterInAvail = availableNum.find(evicted);
                if (iterInAvail != availableNum.end()) {
                    //注意这里一开始写的是erase(evicted)，该写法会将集合内所有与evicted相等的元素删除，不符合期望。
                    availableNum.erase(iterInAvail);
                    sum -=evicted;
                } else if (minKset.find(evicted) != minKset.end()) {
                    auto iter = minKset.find(evicted);
                    minKset.erase(iter);
                    int minInAvailableSet = *(availableNum.begin());
                    minKset.insert(minInAvailableSet);
                    availableNum.erase(availableNum.begin());
                    sum -=minInAvailableSet;
                } else {
                    auto iter = maxKset.find(evicted);
                    maxKset.erase(iter);
                    int maxInAvailableSet = *(availableNum.cbegin());
                    maxKset.insert(maxInAvailableSet);
                    availableNum.erase(prev(availableNum.end()));
                    sum -=maxInAvailableSet;
                }
            }
            int maxInMinKset = *(minKset.rbegin()), minInMaxKset = *(maxKset.begin());
            if (num >= maxInMinKset && num <= minInMaxKset) {
                availableNum.insert(num);
                sum +=num;
            } else if (num < maxInMinKset) {
                //num属于最小k集合内
                minKset.erase(prev(minKset.end()));
                minKset.insert(num);
                availableNum.insert(maxInMinKset);
                sum +=maxInMinKset;
            } else {
                maxKset.erase(maxKset.begin());
                maxKset.insert(num);
                availableNum.insert(minInMaxKset);
                sum +=minInMaxKset;
            }
        }
        numberStream.push( num ); //按顺序记录插入的num
    }

    int calculateMKAverage() {
        if( numberStream.size() < m_ )
            return -1;
        return sum / ( m_ - 2 * k_ );
    }
};

int main(){
    MKAverage mkAverage(5,2);
    mkAverage.addElement(3);
    mkAverage.addElement(1);
    cout<<mkAverage.calculateMKAverage()<<endl; //-1
    mkAverage.addElement(8);
    mkAverage.addElement(2);
    mkAverage.addElement(7);
    cout<<mkAverage.calculateMKAverage()<<endl; //3
    mkAverage.addElement(1);
    cout<<mkAverage.calculateMKAverage()<<endl; //2
    mkAverage.addElement(4);
    mkAverage.addElement(6);
    cout<<mkAverage.calculateMKAverage()<<endl; //4
    return 0;
}