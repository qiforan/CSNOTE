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
    int pathSum(TreeNode *root, int sum)
    {
        s = sum;
        helper(root, 0);
        return ret;
    }

private:
    unordered_map<int, int> mp;
    int ret = 0;
    int s;

    void helper(TreeNode *root, int cur)
    {
        if (root == nullptr)
            return;
        cur += root->val;
        mp[cur]++;
        if (s != 0)
            ret += mp[cur - s];
        else
            ret += mp[cur - s] - 1;
        if (cur == s)
            ret++;
        helper(root->left, cur);
        helper(root->right, cur);
        mp[cur]--;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//You are given a binary tree in which each node contains an integer value. 
//
// Find the number of paths that sum to a given value. 
//
// The path does not need to start or end at the root or a leaf, but it must go 
//downwards
//(traveling only from parent nodes to child nodes). 
//
// The tree has no more than 1,000 nodes and the values are in the range -1,000,
//000 to 1,000,000.
//
// Example:
// 
//root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
//
//      10
//     /  \
//    5   -3
//   / \    \
//  3   2   11
// / \   \
//3  -2   1
//
//Return 3. The paths that sum to 8 are:
//
//1.  5 -> 3
//2.  5 -> 2 -> 1
//3. -3 -> 11
// 
// Related Topics 树 
// 👍 696 👎 0
