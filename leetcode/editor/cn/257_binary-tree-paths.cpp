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
    vector<string> binaryTreePaths(TreeNode *root)
    {
        if(root)
            helper(root,"");
        return ret;
    }
private:
    vector<string> ret;
    void helper(TreeNode *root, string cur){
        cur += to_string(root->val);
        if(root->left == nullptr && root->right == nullptr){
            ret.push_back(cur);
            return;
        }
        if(root->left)
            helper(root->left,cur+"->");
        if(root->right)
            helper(root->right,cur+"->");
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given a binary tree, return all root-to-leaf paths. 
//
// Note: A leaf is a node with no children. 
//
// Example: 
//
// 
//Input:
//
//   1
// /   \
//2     3
// \
//  5
//
//Output: ["1->2->5", "1->3"]
//
//Explanation: All root-to-leaf paths are: 1->2->5, 1->3
// Related Topics 树 深度优先搜索 
// 👍 417 👎 0
