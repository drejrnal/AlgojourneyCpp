//
// Created by luoxiYun on 2021/4/18.
// 包括常见异或(和)题目及重要结论
//

#include "common.h"
#include "NumTrie.h"


class XorProblem{

public:
    /*
     * 计算1~n的异或和
     * 常规操作：遍历1~n,求异或和，复杂度O(n)；利用下图异或和特殊分布，O(1)解决：
     * 即 每隔4个数，有一定规律，4的倍数刚好等于n，模4余3刚好等于0
     * Number Binary-Repr  XOR-from-1-to-n
     * 1         1           [0001]
     * 2        10           [0011]
     * 3        11           [0000]  <----- We get a 0
     * 4       100           [0100]  <----- Equals to n
     * 5       101           [0001]
     * 6       110           [0111]
     * 7       111           [0000]  <----- We get 0
     * 8      1000           [1000]  <----- Equals to n
     * 9      1001           [0001]
     * 10     1010           [1011]
     * 11     1011           [0000]  <------ We get 0
     * 12     1100           [1100]  <------ Equals to n
     */
    int computeXorSum( int n ){
        if( n % 4 == 0 )
            return n;
        if( n % 4 == 1 )
            return 1;
        if( n % 4 == 2 )
            return n+1;
        return 0;
    }

    /*
     * 利用前缀树(节点表示数字的bit field)求异或和
     */

    //计算插入number后，在当前numTrie集合内每两个数的最大异或和
    int maxXorUntil( numTrie *building, int number ){
        numTrieNode *trav = building->getRoot();
        for( int i = BITINT_MAX-1; i >= 0; i-- ){
            if( trav->children[ 1 - (number>>i)&1 ] != nullptr )
                trav = trav->children[ 1 - (number>>i)&1 ];
            else
                trav = trav->children[ (number>>i)&1 ];
        }
        return trav->value ^ number;
    }

    int maxTwoNumberXor( vector<int> &nums ){
        int result = 0;
        numTrie numBuilding;
        numBuilding.insert( nums[0] );
        for( int i = 1; i < nums.size(); i++ ){
            result = max( result, maxXorUntil(&numBuilding, nums[i]) );
            numBuilding.insert( nums[i] );
        }
        return result;
    }

    /*
     *  力扣1803 统计数值对的异或值在给定范围区间内 [@Param: low, @Param: high] 的对数
     *  题目中给的数的范围在0-20000之间，所以前缀树的高度不超过16
     */

    //计算当前前缀树@Param: numTrie 中与@Param: num 异或值小于@Param: limit的个数
    int countSmaller( numTrie *trie,  int num, int limit ){
        numTrieNode *trav = trie->getRoot();
        int count = 0; //记录结果
        for( int i = BITINT_MAX - 1; i >= 0; i-- ){
            /*
             * 对应下述注释
             */
            if( trav == nullptr )
                return count;
            int num_bit = ( num >> i ) & 1; //num的第i个bit位
            int limit_bit = ( limit >> i ) & 1;
            if( limit_bit ){
                if( trav->children[num_bit] != nullptr )
                    count +=trav->children[num_bit]->count;
                /*
                 * 此时trav可能为nullptr,
                 * 即当前的前缀树各个元素与@Param:num的异或和均小于limit。
                 * 需要在循坏开始处处理
                 */
                trav = trav->children[ 1-num_bit ];
            }else{
                trav = trav->children[num_bit];
            }
        }
        /*
         * 如果循环是遍历到i < 0 处停止，则
         * 说明@Param:num与前缀树中某一元素的异或和与limit相同
         * 直接返回count，也即表明count是小于@Param: limit的总个数
         */
        return count;
    }

    int countPairs( vector<int> &nums, int low, int high ){
        numTrie trie;
        int res = 0;
        trie.insert( nums[0] );
        for( int i = 1; i < nums.size(); i++ ){
            int cnt1 = countSmaller( &trie, nums[i], high+1 );
            cout<<"upper limit:"<<cnt1<<endl;
            int cnt2 = countSmaller( &trie, nums[i], low );
            cout<<"lower limit:"<<cnt2<<endl;
            res += (cnt1 - cnt2);
            trie.insert( nums[i] );
        }
        return res;
    }


    //力扣1707 maximum xor with an element from an array
    vector<int> maximizeXor( vector<int> &nums, vector<vector<int>> &queries ){
        using qp_type = pair<int, int>;
        priority_queue<qp_type, vector<qp_type>, greater<qp_type>> pq;
        numTrie numBuilding;
        for( int i = 0; i < queries.size(); i++ ){
            pq.push( {queries[i][1], i} );
        }
        sort( nums.begin(), nums.end() );
        vector<int> result;
        result.resize(queries.size());
        int trav = 0;
        while ( !pq.empty() ){
            auto top = pq.top();
            pq.pop();
            while( trav < nums.size() && nums[trav] <= top.first ){
                numBuilding.insert( nums[trav] );
                trav++;
            }
            if( numBuilding.empty() )
                result[top.second] = -1;
            else
                result[top.second] = maxXorUntil( &numBuilding, queries[top.second][0] );
        }
        return result;
    }



    /*
     * Xor of all subarrays( 范围由查询query给出)
     */
    vector<int> xorQueries( vector<int> &nums, vector<vector<int>> &queries ){
        vector<int> xorSum(nums.size(), 0);
        vector<int> result;
        xorSum[0] = nums[0];
        for( int i = 1; i < nums.size(); i++ )
            xorSum[i] ^= xorSum[i-1];
        for( auto arr : queries ){
            if( arr[0] == 0 )
                result.push_back( xorSum[arr[1]]);
            else
                result.push_back( xorSum[arr[1]] ^ xorSum[arr[0]-1]);
        }
        return result;
    }
    /*
     * 根据比特位1或0(数字)的频率计算异或和的结果：
     *  当比特1(某数字)出现的次数为奇数，则结果为比特1(包含该数字)
     *  当比特0(某数字)出现的次数是偶数，则结果为比特0(不包含该数字)
     */

    //求数组各个子数组异或和的异或和
    int getTotalXorOfSubarrayXors(vector<int> &nums){
        int n = nums.size();
        int res = 0;
        //数组中下标为i的元素出现在所有子数组中的频率是i * ( n-i ) + ( n-i )
        for( int i = 0; i < nums.size(); i++ ){
            int freqOfNum = i * ( n - i ) + ( n - i );
            if( freqOfNum & 1 ) //频率为奇数，则总异或和包含该数
                res ^=nums[i];
            //若为偶数，则总异或和不包含该数字
        }
        return res;
    }

    //naive approach求总异或和
    int naiveGetSubarrayXors( vector<int> &nums ){
        int res = 0;
        for( int i = 0; i < nums.size(); i++ ){
            for( int j = i; j < nums.size(); j++ ){
                int temp = 0;
                for( int k = i; k <=j; k++ )
                    temp ^=nums[k];
                res ^=temp;
            }
        }
        return res;
    }

};

int main(){
    XorProblem xorProblem;
    //vector<int> nums = { 14,70,53,83,49,92,51,66,70 };
    /*if(xorProblem.getTotalXorOfSubarrayXors(nums)!=xorProblem.naiveGetSubarrayXors(nums)){
        cout<<"===error==="<<endl;
    }*/
    //cout<<xorProblem.maxTwoNumberXor(nums)<<endl;
    vector<int> nums = { 1,4,2, 7 };
    int low = 2, high = 6;
    cout<<xorProblem.countPairs( nums, low, high );
    return 0;
}