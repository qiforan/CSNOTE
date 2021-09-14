#include <bits/stdc++.h>
using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        const int m = obstacleGrid.size();
        const int n = obstacleGrid[0].size();
        vector<int> dp(n,1);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                // obstacle
                if(obstacleGrid[i][j]){
                    dp[j] = 0;
                }
                else if(i == 0 && j > 0)
                    dp[j] = dp[j-1];
                else if(j > 0 && i > 0)
                    dp[j] += dp[j-1];
//                printf("dp[%d][%d] = %d\n",i,j,dp[j]);
            }
        }
        return dp[n-1];
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//A robot is located at the top-left corner of a m x n grid (marked 'Start' in t
//he diagram below). 
//
// The robot can only move either down or right at any point in time. The robot 
//is trying to reach the bottom-right corner of the grid (marked 'Finish' in the d
//iagram below). 
//
// Now consider if some obstacles are added to the grids. How many unique paths 
//would there be? 
//
// An obstacle and space is marked as 1 and 0 respectively in the grid. 
//
// 
// Example 1: 
//
// 
//Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
//Output: 2
//Explanation: There is one obstacle in the middle of the 3x3 grid above.
//There are two ways to reach the bottom-right corner:
//1. Right -> Right -> Down -> Down
//2. Down -> Down -> Right -> Right
// 
//
// Example 2: 
//
// 
//Input: obstacleGrid = [[0,1],[0,0]]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// m == obstacleGrid.length 
// n == obstacleGrid[i].length 
// 1 <= m, n <= 100 
// obstacleGrid[i][j] is 0 or 1. 
// 
// Related Topics 数组 动态规划 
// 👍 460 👎 0
