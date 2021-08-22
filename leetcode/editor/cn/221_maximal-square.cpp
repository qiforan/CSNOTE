#include <bits/stdc++.h>
using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.size() == 0 || matrix[0].size() == 0)
            return 0;
        const int r = matrix.size();
        const int c = matrix[0].size();
        int ret = 0;
        vector<vector<int>> dp(r, vector<int>(c, 0));
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if(matrix[i][j] == '1'){
                    if(i == 0 || j == 0)
                        dp[i][j] = 1;
                    else{
                        dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1]) + 1;
                    }
                }
                ret = max(ret,dp[i][j]);
            }
        }
        return ret * ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given an m x n binary matrix filled with 0's and 1's, find the largest square 
//containing only 1's and return its area. 
//
// 
// Example 1: 
//
// 
//Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1",
//"1"],["1","0","0","1","0"]]
//Output: 4
// 
//
// Example 2: 
//
// 
//Input: matrix = [["0","1"],["1","0"]]
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: matrix = [["0"]]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// m == matrix.length 
// n == matrix[i].length 
// 1 <= m, n <= 300 
// matrix[i][j] is '0' or '1'. 
// 
// Related Topics 动态规划 
// 👍 634 👎 0
