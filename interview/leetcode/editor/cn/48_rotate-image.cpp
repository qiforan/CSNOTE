#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    void rotate(vector<vector<int>> &matrix)
    {
        const int n = matrix.size();
        for (int k = n; k > 0; k -= 2) {
            for (int i = 0; i + 1 < k; i++)
                swap(matrix[(n - k) / 2 + 0][(n - k) / 2 + i],
                     matrix[(n - k) / 2 + i][n - 1 - (n - k) / 2],
                     matrix[n - 1 - (n - k) / 2][n - 1 - (n - k) / 2 - i],
                     matrix[n - 1 - (n - k) / 2 - i][(n - k) / 2]);
        }
    }

private:
    void swap(int &a, int &b, int &c, int &d)
    {
//        printf("a = %d b =%d c = %d d = %d\n", a, b, c, d);
        int temp = d;
        d = c;
        c = b;
        b = a;
        a = temp;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//You are given an n x n 2D matrix representing an image, rotate the image by 90
// degrees (clockwise). 
//
// You have to rotate the image in-place, which means you have to modify the inp
//ut 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation. 
//
// 
// Example 1: 
//
// 
//Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
//Output: [[7,4,1],[8,5,2],[9,6,3]]
// 
//
// Example 2: 
//
// 
//Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
//Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
// 
//
// Example 3: 
//
// 
//Input: matrix = [[1]]
//Output: [[1]]
// 
//
// Example 4: 
//
// 
//Input: matrix = [[1,2],[3,4]]
//Output: [[3,1],[4,2]]
// 
//
// 
// Constraints: 
//
// 
// matrix.length == n 
// matrix[i].length == n 
// 1 <= n <= 20 
// -1000 <= matrix[i][j] <= 1000 
// 
// Related Topics 数组 
// 👍 726 👎 0
