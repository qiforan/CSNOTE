#include <bits/stdc++.h>
using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        const int n = prices.size();
        if(n == 0) return 0;
        // 0 - have
        // 1 - frozen
        // 2 - free to buy
        vector<vector<int>> dp(n,vector<int>(3,0));
        dp[0][0] -= prices[0];
        for(int i = 1; i  < n; i++){
            // do nothing or buy a stock
            dp[i][0] = max(dp[i-1][0],dp[i-1][2] - prices[i]);
            // sold a stock
            dp[i][1] = dp[i-1][0] + prices[i];
            dp[i][2] = max(dp[i-1][1],dp[i-1][2]);
        }
        return max(dp[n-1][1],dp[n-1][2]);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Say you have an array for which the ith element is the price of a given stock 
//on day i. 
//
// Design an algorithm to find the maximum profit. You may complete as many tran
//sactions as you like (ie, buy one and sell one share of the stock multiple times
//) with the following restrictions: 
//
// 
// You may not engage in multiple transactions at the same time (ie, you must se
//ll the stock before you buy again). 
// After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 
//day) 
// 
//
// Example: 
//
// 
//Input: [1,2,3,0,2]
//Output: 3 
//Explanation: transactions = [buy, sell, cooldown, buy, sell]
// Related Topics 动态规划 
// 👍 637 👎 0
