#include <bits/stdc++.h>
using namespace std;

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        helper(root);
        return ret;
    }
private:
    int ret = 0;
    void helper(TreeNode *root){
        if(root == nullptr)
            return;
        if(root->left && root->left->left==nullptr && root->left->right ==nullptr)
            ret += root->left->val;
        helper(root->left);
        helper(root->right);
    }

};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Find the sum of all left leaves in a given binary tree. 
//
// Example:
// 
//    3
//   / \
//  9  20
//    /  \
//   15   7
//
//There are two left leaves in the binary tree, with values 9 and 15 respectivel
//y. Return 24.
// 
// Related Topics 树 
// 👍 269 👎 0
