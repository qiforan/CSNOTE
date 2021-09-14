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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        const int n = inorder.size();
        return helper(0,n-1,0,n-1,inorder,postorder);
    }

private:
    TreeNode *
    helper(int in_l, int in_r, int post_l, int post_r, const vector<int> &inorder, const vector<int> &postorder)
    {
        if (in_l > in_r)
            return NULL;
        int val = postorder[post_r];
        int pos = find(inorder.begin() + in_l, inorder.begin() + in_r + 1, val) - inorder.begin() -
                  in_l;
        TreeNode * root = new TreeNode(val);
        root->left = helper(in_l,in_l + pos-1, post_l,post_l+pos-1,inorder,postorder);
        root->right = helper(in_l+pos+1,in_r,post_l+pos,post_r-1,inorder,postorder);
        return root;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given inorder and postorder traversal of a tree, construct the binary tree. 
//
// Note: 
//You may assume that duplicates do not exist in the tree. 
//
// For example, given 
//
// 
//inorder = [9,3,15,20,7]
//postorder = [9,15,7,20,3] 
//
// Return the following binary tree: 
//
// 
//    3
//   / \
//  9  20
//    /  \
//   15   7
// 
// Related Topics 树 深度优先搜索 数组 
// 👍 423 👎 0
