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
    int sumNumbers(TreeNode *root)
    {
        if (root)
            helper(root, 0);
        return ret;
    }

private:
    int ret = 0;

    void helper(TreeNode *root, int cur)
    {
        cur = cur * 10 + root->val;
        if (root->left == NULL && root->right == NULL)
            ret += cur;
        if (root->left != NULL)
            helper(root->left, cur);
        if (root->right != NULL)
            helper(root->right, cur);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given a binary tree containing digits from 0-9 only, each root-to-leaf path co
//uld represent a number. 
//
// An example is the root-to-leaf path 1->2->3 which represents the number 123. 
//
//
// Find the total sum of all root-to-leaf numbers. 
//
// Note: A leaf is a node with no children. 
//
// Example: 
//
// 
//Input: [1,2,3]
//    1
//   / \
//  2   3
//Output: 25
//Explanation:
//The root-to-leaf path 1->2 represents the number 12.
//The root-to-leaf path 1->3 represents the number 13.
//Therefore, sum = 12 + 13 = 25. 
//
// Example 2: 
//
// 
//Input: [4,9,0,5,1]
//    4
//   / \
//  9   0
// / \
//5   1
//Output: 1026
//Explanation:
//The root-to-leaf path 4->9->5 represents the number 495.
//The root-to-leaf path 4->9->1 represents the number 491.
//The root-to-leaf path 4->0 represents the number 40.
//Therefore, sum = 495 + 491 + 40 = 1026. 
// Related Topics 树 深度优先搜索 
// 👍 297 👎 0
