#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        const int m = matrix.size();
        const int n =  m == 0 ? 0 : matrix[0].size();
        dp.resize(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = matrix[i - 1][j - 1] + dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1];
            }
        }
    }

    vector<vector<int>> dp;

    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2 + 1][col2 + 1] - dp[row2 + 1][col1 ] - dp[row1 ][col2 + 1] + dp[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
//leetcode submit region end(Prohibit modification and deletion)


int main() {
    return 0;
}

//Given a 2D matrix matrix, find the sum of the elements inside the rectangle de
//fined by its upper left corner (row1, col1) and lower right corner (row2, col2).
// 
//
// 
// 
//The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) 
//and (row2, col2) = (4, 3), which contains sum = 8.
// 
//
// Example: 
// 
//Given matrix = [
//  [3, 0, 1, 4, 2],
//  [5, 6, 3, 2, 1],
//  [1, 2, 0, 1, 5],
//  [4, 1, 0, 1, 7],
//  [1, 0, 3, 0, 5]
//]
//
//sumRegion(2, 1, 4, 3) -> 8
//sumRegion(1, 1, 2, 2) -> 11
//sumRegion(1, 2, 2, 4) -> 12
// 
// 
//
// Note: 
// 
// You may assume that the matrix does not change. 
// There are many calls to sumRegion function. 
// You may assume that row1 ≤ row2 and col1 ≤ col2. 
// 
// Related Topics 动态规划 
// 👍 132 👎 0
