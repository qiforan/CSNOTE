#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr)
    {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right)
    {}
};

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int kthSmallest(TreeNode *root, int k)
    {
        int cur = 0;
        helper(root,cur,k);
        return ret;
    }
private:
    int ret;
    void helper(TreeNode *root, int& cur,int target){
        if(root == nullptr)
            return;
        helper(root->left,cur,target);
        cur++;
        if(cur == target)
            ret = root->val;
        helper(root->right,cur,target);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given a binary search tree, write a function kthSmallest to find the kth small
//est element in it. 
//
// 
//
// Example 1: 
//
// 
//Input: root = [3,1,4,null,2], k = 1
//   3
//  / \
// 1   4
//  \
//   2
//Output: 1 
//
// Example 2: 
//
// 
//Input: root = [5,3,6,2,4,null,null,1], k = 3
//       5
//      / \
//     3   6
//    / \
//   2   4
//  /
// 1
//Output: 3
// 
//
// Follow up: 
//What if the BST is modified (insert/delete operations) often and you need to f
//ind the kth smallest frequently? How would you optimize the kthSmallest routine?
// 
//
// 
// Constraints: 
//
// 
// The number of elements of the BST is between 1 to 10^4. 
// You may assume k is always valid, 1 ≤ k ≤ BST's total elements. 
// 
// Related Topics 树 二分查找 
// 👍 330 👎 0
