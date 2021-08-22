#include <bits/stdc++.h>
using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        vector<vector<int>> v({{2,0},{3,0},{5,0}});
        dp[0] = 1;
        for(int i = 1; i < n; i++){
            int cur = INT_MAX;
            int index;
            for(int j = 0; j < 3; j++){
                if(cur > v[j][0] * dp[v[j][1]]){
                    index = j;
                    cur = v[j][0] * dp[v[j][1]];
                }
            }
            dp[i] = cur;
            for(int j = 0; j < 3; j++)
                if(v[j][0] * (dp[v[j][1]]) <= cur)
                    v[j][1]++;
        }
        return dp[n-1];
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    cout << s.nthUglyNumber(20);
    return 0;
}

//Write a program to find the n-th ugly number. 
//
// Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
//
// Example: 
//
// 
//Input: n = 10
//Output: 12
//Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ug
//ly numbers. 
//
// Note: 
//
// 
// 1 is typically treated as an ugly number. 
// n does not exceed 1690. 
// Related Topics 堆 数学 动态规划 
// 👍 441 👎 0
