#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int coinChange(vector<int> &coins, int amount)
    {
        const int n = coins.size();
        vector<vector<int>> dp(1 + amount, vector<int>(n, -1));
        // 初值
        for (int i = 0; i < n; i++)
            dp[0][i] = 0;
        // 状态转移
        for (int i = 0; i < n; i++)
            for (int j = 1; j <= amount; j++) {
                int pre = j - coins[i];
                if (pre >= 0 && dp[pre][i] != -1)
                    dp[j][i] = 1 + dp[pre][i];
                if (i > 0 && dp[j][i - 1] != -1)
                    if (dp[j][i] == -1)
                        dp[j][i] = dp[j][i - 1];
                    else dp[j][i] = min(dp[j][i], dp[j][i - 1]);

            }

        return dp[amount][n - 1];
    }

};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> coins{1, 2, 5};
    cout << s.coinChange(coins, 11);
    return 0;
}

//You are given coins of different denominations and a total amount of money amo
//unt. Write a function to compute the fewest number of coins that you need to mak
//e up that amount. If that amount of money cannot be made up by any combination o
//f the coins, return -1. 
//
// You may assume that you have an infinite number of each kind of coin. 
//
// 
// Example 1: 
//
// 
//Input: coins = [1,2,5], amount = 11
//Output: 3
//Explanation: 11 = 5 + 5 + 1
// 
//
// Example 2: 
//
// 
//Input: coins = [2], amount = 3
//Output: -1
// 
//
// Example 3: 
//
// 
//Input: coins = [1], amount = 0
//Output: 0
// 
//
// Example 4: 
//
// 
//Input: coins = [1], amount = 1
//Output: 1
// 
//
// Example 5: 
//
// 
//Input: coins = [1], amount = 2
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// 1 <= coins.length <= 12 
// 1 <= coins[i] <= 231 - 1 
// 0 <= amount <= 104 
// 
// Related Topics 动态规划 
// 👍 979 👎 0
