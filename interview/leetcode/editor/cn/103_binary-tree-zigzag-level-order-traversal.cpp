#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL)
    {}
};

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        bool flag = false;
        queue<TreeNode *> q;
        if (root)
            q.push(root);
        while (q.size()) {
            ret.push_back({});
            int n = q.size();
            for (int i = 0; i < n; i++) {
                TreeNode *top = q.front();
                q.pop();
                ret.back().push_back(top->val);
                TreeNode *left, *right;
                left = top->left;
                right = top->right;
                if (left)
                    q.push(left);
                if (right)
                    q.push(right);
            }
            if (flag)
                reverse(ret.back().begin(), ret.back().end());
            flag = !flag;
        }
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given a binary tree, return the zigzag level order traversal of its nodes' val
//ues. (ie, from left to right, then right to left for the next level and alternat
//e between). 
//
// 
//For example: 
//Given binary tree [3,9,20,null,null,15,7], 
// 
//    3
//   / \
//  9  20
//    /  \
//   15   7
// 
// 
// 
//return its zigzag level order traversal as: 
// 
//[
//  [3],
//  [20,9],
//  [15,7]
//]
// 
// Related Topics 栈 树 广度优先搜索 
// 👍 362 👎 0
