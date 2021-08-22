#include <bits/stdc++.h>
using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int cuttingRope(int n) {
        vector<int> dp(n+1);
        dp[1] = dp[2] = 1;
        for(int i = 3; i <= n; i++){
            dp[i] = i;
            for(int j = 1; j <= n-1; j++)
                dp[i] = max(dp[i], (i-j)*dp[j]);
        }
        return dp[n];
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    s.cuttingRope(3);
    return 0;
}

//English description is not available for the problem. Please switch to Chinese
//. Related Topics 数学 动态规划 
// 👍 140 👎 0
