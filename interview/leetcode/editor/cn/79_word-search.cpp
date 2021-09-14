#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size();
        n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                helper(i, j, visited,board, word, 0);
        return ret;
    }

private:
    bool ret = false;
    int m, n;
    vector<vector<int>> v{{0,  1},
                          {0,  -1},
                          {1,  0},
                          {-1, 0}};

    void
    helper(int i, int j, vector<vector<bool>> &visited, const vector<vector<char>> &board, const string &word, int pos)
    {
        if (ret) return;
        if (pos >= word.size()) {
            ret = true;
        }
        if (i < 0 || j < 0 || i >= m || j >= n || visited[i][j] || board[i][j] != word[pos])
            return;
        visited[i][j] = true;
        for (int k = 0; k < 4; k++)
            helper(i + v[k][0], j + v[k][1], visited, board, word, pos+1);
        visited[i][j] = false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
//    cout << s.exist(board,"ABCCED");
//    cout << s.exist(board,"SEE");
    cout << s.exist(board,"ABCD");
    return 0;
}

//Given an m x n board and a word, find if the word exists in the grid. 
//
// The word can be constructed from letters of sequentially adjacent cells, wher
//e "adjacent" cells are horizontally or vertically neighboring. The same letter c
//ell may not be used more than once. 
//
// 
// Example 1: 
//
// 
//Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "ABCCED"
//Output: true
// 
//
// Example 2: 
//
// 
//Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "SEE"
//Output: true
// 
//
// Example 3: 
//
// 
//Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "ABCB"
//Output: false
// 
//
// 
// Constraints: 
//
// 
// m == board.length 
// n = board[i].length 
// 1 <= m, n <= 200 
// 1 <= word.length <= 103 
// board and word consists only of lowercase and uppercase English letters. 
// 
// Related Topics 数组 回溯算法 
// 👍 716 👎 0
