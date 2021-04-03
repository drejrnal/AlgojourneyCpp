//
// Created by luoxiYun on 2021/3/25.
//

#include "common.h"

class StockMarket{

public:
    //考虑在第i个交易日有两种状态：买股票和卖股票
    int mostProfitableWithinK( vector<int> &prices, int k ){
        //在prices[0...i]价格区间进行最多k次交易所获得的最大利润
        vector<vector<int>> dp( prices.size(), vector<int>( 2 * k + 1, 0 ));
        for( int i = 1; i < 2*k; i+=2 )
            dp[0][i] = -prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            for( int j = 0; j < 2 * k -1; j+=2 ){
                dp[i][j+1] = max( dp[i-1][j+1], dp[i-1][j] - prices[i] );
                dp[i][j+2] = max( dp[i-1][j+2], dp[i-1][j+1] + prices[i] );
            }
        }
        return dp[prices.size()-1][2*k];
    }

    int mostProfitable2Trades( vector<int> &prices ){

        vector<vector<int>> dp( prices.size(),vector<int>(5, 0) );
        for( int k = 1; k < 5; k+=2 )
            dp[0][k] = -prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            for( int k = 0; k < 5; k+=2 ){
                dp[i][k+1] = max( dp[i-1][k+1], dp[i-1][k] - prices[i] );
                dp[i][k+2] = max( dp[i-1][k+2], dp[i-1][k+1] + prices[i] );
            }
        }
        return dp[prices.size()-1][4];

    }

    int mostProfitableInfinity( vector<int> &prices ){
        int slidingV1 = -prices[0], slidingV2 = 0;
        for( int i = 1; i < prices.size(); i++ ){
            int tmp1 = slidingV1;
            slidingV1 = max( slidingV1, slidingV2 - prices[i] );
            slidingV2 = max( slidingV2, tmp1 + prices[i] );
        }
        return slidingV2;
    }
};

int main(){
    vector<int> prices{ 3, 2, 6, 5, 0, 3 };
    int k = 3;
    StockMarket stockMarket;
    cout<<stockMarket.mostProfitableWithinK( prices, k )<<endl;
    return 0;
}