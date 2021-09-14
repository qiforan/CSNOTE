#include <bits/stdc++.h>

using namespace std;


// Definition for a binary tree node.
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        const int n = preorder.size();
        return helper(0, n - 1, 0, n - 1, preorder, inorder);
    }

private:
    TreeNode *helper(int pre_l, int pre_r, int in_l, int in_r, const vector<int> &preorder, const vector<int> &inorder)
    {
//        printf("%d %d %d %d\n",pre_l,pre_r,in_l,in_r);
        if (pre_l > pre_r)
            return NULL;
        int val = preorder[pre_l];
        int pos = find(inorder.begin() + in_l, inorder.begin() + in_r + 1, val) - inorder.begin() - in_l;
//        printf("%d %d\n",val,pos);
        TreeNode *root = new TreeNode(val);
        root->left = helper(pre_l + 1, pre_l + pos, in_l, in_l + pos - 1, preorder, inorder);
        root->right = helper(pre_l + pos + 1, pre_r, in_l + pos + 1, in_r, preorder, inorder);
        return root;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> pre{3,9,20,15,7};
    vector<int> in{9,3,15,20,7};
    s.buildTree(pre,in);
    return 0;
}

//Given preorder and inorder traversal of a tree, construct the binary tree. 
//
// Note: 
//You may assume that duplicates do not exist in the tree. 
//
// For example, given 
//
// 
//preorder = [3,9,20,15,7]
//inorder = [9,3,15,20,7] 
//
// Return the following binary tree: 
//
// 
//    3
//   / \
//  9  20
//    /  \
//   15   7 
// Related Topics 树 深度优先搜索 数组 
// 👍 809 👎 0
