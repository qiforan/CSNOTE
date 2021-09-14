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
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> ret;
        queue<TreeNode *> q;
        if(root)
            q.push(root);
        while(q.size()){
            int n = q.size();
            for(int i = 0; i < n;i++){
                TreeNode * top = q.front();
                q.pop();
                if(top->left)
                    q.push(top->left);
                if(top->right)
                    q.push(top->right);
                if(i == n-1)
                    ret.push_back(top->val);
            }
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

//Given a binary tree, imagine yourself standing on the right side of it, return
// the values of the nodes you can see ordered from top to bottom. 
//
// Example: 
//
// 
//Input: [1,2,3,null,5,null,4]
//Output: [1, 3, 4]
//Explanation:
//
//   1            <---
// /   \
//2     3         <---
// \     \
//  5     4       <---
// Related Topics 树 深度优先搜索 广度优先搜索 
// 👍 383 👎 0
