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
    int countNodes(TreeNode *root)
    {
        int ret = 0;
        helper(root,ret);
        return ret;
    }
private:
    void helper(TreeNode *root,int& cnt)
    {
        if(root == NULL)
            return;
        cnt++;
        helper(root->left, cnt);
        helper(root->right,cnt);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given a complete binary tree, count the number of nodes. 
//
// Note: 
//
// Definition of a complete binary tree from Wikipedia: 
//In a complete binary tree every level, except possibly the last, is completely
// filled, and all nodes in the last level are as far left as possible. It can hav
//e between 1 and 2h nodes inclusive at the last level h. 
//
// Example: 
//
// 
//Input: 
//    1
//   / \
//  2   3
// / \  /
//4  5 6
//
//Output: 6 
// Related Topics 树 二分查找 
// 👍 412 👎 0
