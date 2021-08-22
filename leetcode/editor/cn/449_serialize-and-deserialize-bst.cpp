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
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
    }
private:
    vector<string> ret;
    void to_vector(TreeNode *root){
        queue<TreeNode *> q;
        bool flag = true;
        while(flag){
            flag = false;
            int n = q.size();
            for(int i = 0; i < n; i++){
                TreeNode *top = q.front();
                q.pop();
                if(top){
                    ret.push_back(to_string(top->val));
                    q.push(top->left);
                    q.push(top->right);
                    flag = true;
                }
                else{
                    ret.push_back("null");
                    q.push(NULL);
                    q.push(NULL);
                }
            }
        }
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Serialization is converting a data structure or object into a sequence of bits
// so that it can be stored in a file or memory buffer, or transmitted across a ne
//twork connection link to be reconstructed later in the same or another computer 
//environment. 
//
// Design an algorithm to serialize and deserialize a binary search tree. There 
//is no restriction on how your serialization/deserialization algorithm should wor
//k. You need to ensure that a binary search tree can be serialized to a string, a
//nd this string can be deserialized to the original tree structure. 
//
// The encoded string should be as compact as possible. 
//
// 
// Example 1: 
// Input: root = [2,1,3]
//Output: [2,1,3]
// Example 2: 
// Input: root = []
//Output: []
// 
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 104]. 
// 0 <= Node.val <= 104 
// The input tree is guaranteed to be a binary search tree. 
// 
// Related Topics 树 
// 👍 142 👎 0
