# Walking Algorithm - 算法题解与数据结构实现记录

![编程语言](https://img.shields.io/badge/language-C++-blue.svg)
![许可证](https://img.shields.io/badge/license-MIT-green.svg)

## 🌟 项目概述

Walking Algorithm 是一个记录我在算法学习过程中的题解实现与思考的仓库。项目包含了大量 LeetCode
算法题目及其他编程竞赛中出现的经典算法题目的解法。项目根据不同的算法类型和解题策略进行了精心分类整理，使用 C++语言进行编码。

本项目特点:

-   **系统化分类**：将相似题型归类，便于系统掌握算法思想
-   **模板化实现**：提炼出常用数据结构的模板结构，方便快速应用
-   **系列化学习**：题目整合，完整实现了多个经典题型系列（如最短路径系列，背包问题系列，二分查找系列）

## 📋 目录

- [Walking Algorithm - 算法题解与数据结构实现记录](#walking-leetcode---算法题解与数据结构实现记录)
  - [🌟 项目概述](#-项目概述)
  - [📋 目录](#-目录)
  - [🏗️ 数据结构实现](#️-数据结构实现)
    - [通用模板类数据结构](#通用模板类数据结构)
    - [专用数据结构](#专用数据结构)
  - [🧮 算法分类](#-算法分类)
    - [动态规划系列](#动态规划系列)
      - [股票问题系列(dp/stock\_market.cpp)](#股票问题系列dpstock_marketcpp)
      - [背包问题系列(dp/back\_pack.cpp)](#背包问题系列dpback_packcpp)
      - [其他经典动态规划问题](#其他经典动态规划问题)
    - [图论算法](#图论算法)
      - [DFS/BFS](#dfsbfs)
      - [并查集](#并查集)
      - [最短路径 `graph/shortest_path.cpp`](#最短路径-graphshortest_pathcpp)
      - [使用拓扑排序解题 - `graph/topology.cpp`](#使用拓扑排序解题---graphtopologycpp)
      - [其余经典图论算法](#其余经典图论算法)
    - [字符串与数组处理](#字符串与数组处理)
    - [回溯算法](#回溯算法)
    - [排序与贪心算法](#排序与贪心算法)
      - [归并排序及其应用](#归并排序及其应用)
      - [二分法 - `sort_greedy/search_sorted_array.cpp`](#二分法---sort_greedysearch_sorted_arraycpp)
      - [贪心策略](#贪心策略)
    - [栈](#栈)
      - [单调栈 - `stack_related/monotonous_stack.cpp`](#单调栈---stack_relatedmonotonous_stackcpp)
      - [表达式求值与语法分析](#表达式求值与语法分析)
    - [经典算法](#经典算法)
      - [Quick-select 和 Quick-sort](#quick-select-和-quick-sort)
      - [字符串匹配](#字符串匹配)
  - [🚀 项目构建](#-项目构建)
  - [📖 使用方法](#-使用方法)
  - [📜 许可证](#-许可证)

## 🏗️ 数据结构实现

### 通用模板类数据结构

项目中实现了多种可复用的数据结构模板，定义在 include 目录下，这些模板是解决多种算法问题的基础：

-   **索引优先队列（Indexed Priority Queue）**：`include/indexed_priority_queue.h` - 扩展了标准优先队列，支持 `O(log n)` 时间复杂度的键值更新操作
-   **字典树（Trie & NumTrie）**：`include/Trie.h`、`include/NumTrie.h` - 高效的前缀树实现，分别用于字符串和数值数据
-   **树状数组（Binary Indexed Tree）**：`include/biIndexTree.h` - 针对区间查询和更新进行了优化

### 专用数据结构

-   **中位数查找器（MedianFinder）**：`data_structure_design/medianFinder.cpp` - 高效实现常数时间复杂度的中位数查找
-   **移动平均值计算器（MKAverage）**：`data_structure_design/MKAverage.cpp` - 计算移动窗口中 K 个元素的平均值

## 🧮 算法分类

### 动态规划系列

#### 股票问题系列(dp/stock_market.cpp)

-   K 次交易限制下的最大利润
-   无限次交易的最大利润
-   含冷却期的交易策略

#### 背包问题系列(dp/back_pack.cpp)

-   0/1 背包问题
-   完全背包问题
-   多维约束背包问题
-   等分割集合问题

#### 其他经典动态规划问题

-   最长递增子序列（LIS）dp/LIS.cpp
-   回文串系列问题 dp/palindrone_series.cpp
-   单词拆分变种 dp/word_break.cpp
-   打家劫舍系列 dp/house_robber.cpp

### 图论算法

#### DFS/BFS

-   双向 BFS - `graph/word_ladder.cpp`

#### 并查集

-   冗余连接 - `graph/redundant_connection.cpp`

#### 最短路径 `graph/shortest_path.cpp`

-   Dijkstra 算法
-   Bellman-Ford 算法
-   Floyd-Warshall 算法

#### 使用拓扑排序解题 - `graph/topology.cpp`

-   课程安排问题
-   任务依赖关系

#### 其余经典图论算法

-   Tarjan 算法 - `graph/tarjan.cpp`

### 字符串与数组处理

-   滑动窗口技术
-   双指针算法
-   前缀和应用

### 回溯算法

-   排列组合生成器
-   约束满足问题
-   剪枝技术

### 排序与贪心算法

#### 归并排序及其应用

-   二路归并、区间和 - `sort_greedy/merge_sort_ext.cpp`
-   多路归并 - `sort_greedy/multiway_merge.cpp`

#### 二分法 - `sort_greedy/search_sorted_array.cpp`

-   经典二分查找
-   旋转数组二分查找

#### 贪心策略

-   区间调度问题 - `sort_greedy/interval_scheduling.cpp`
-   最优选择策略 - `sort_greedy/greedy_choice.cpp`

### 栈

#### 单调栈 - `stack_related/monotonous_stack.cpp`

-   矩形面积

#### 表达式求值与语法分析

-   表达式求值（带括号、考虑运算符优先级） - `stack_related/expression_eval.cpp`
-   Lisp 语法分析 - `stack_related/lisp_parser.cpp`

### 经典算法

#### Quick-select 和 Quick-sort

- 寻找数组第K大的数 - `common_algo/Kth_maximum.cpp`

#### 字符串匹配

- KMP算法 - `common_algo/kmp_match.cpp`

## 🚀 项目构建

```bash
# 克隆仓库
git clone https://github.com/yourusername/walking_leetcode.git

# 进入项目目录
cd walking_leetcode

# 创建构建目录
mkdir build && cd build

# 使用CMake构建项目
cmake ..
make
```

## 📖 使用方法

每个算法类别都组织在独立的目录中，公共模板和工具类位于 `include` 目录，便于在实现不同算法时复用。

项目中的代码可以作为算法学习的参考：

```cpp
#include "common.h"
#include "indexed_priority_queue.h"

// 索引优先队列使用示例
int main() {
    indexed_priority_queue<string, int> ipq;
    ipq.push("task1", 5);
    ipq.push("task2", 3);
    ipq.changeKey("task1", 2);  // 更新优先级

    while (!ipq.empty()) {
        auto [key, value] = ipq.top();
        cout << key << ": " << value << endl;
        ipq.pop();
    }

    return 0;
}
```

## 📜 许可证

本项目采用 MIT 许可证 - 详情请查看 [LICENSE](LICENSE) 文件。

---

如果这个项目对你在算法学习上有帮助，请考虑在 GitHub 上给它一个 ⭐ !
