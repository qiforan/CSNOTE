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
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        const int n = nums.size();
        return helper(0,n-1,nums);
    }
private:
    TreeNode *helper(int l, int r, const vector<int> &nums)
    {
        if(l > r)
            return NULL;
        int mid = (l + r) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = helper(l,mid-1,nums);
        root->right = helper(mid+1,r,nums);
        return root;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given an array where elements are sorted in ascending order, convert it to a h
//eight balanced BST. 
//
// For this problem, a height-balanced binary tree is defined as a binary tree i
//n which the depth of the two subtrees of every node never differ by more than 1.
// 
//
// Example: 
//
// 
//Given the sorted array: [-10,-3,0,5,9],
//
//One possible answer is: [0,-3,9,-10,null,5], which represents the following he
//ight balanced BST:
//
//      0
//     / \
//   -3   9
//   /   /
// -10  5
// 
// Related Topics 树 深度优先搜索 
// 👍 668 👎 0
