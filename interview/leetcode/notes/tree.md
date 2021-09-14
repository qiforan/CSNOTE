# 树

## 先序遍历

模拟**递归遍历**时栈的调用，使用栈辅助:

1. 若根节点非空，入栈

2. 栈非空时：

   - 获取出栈元素，并打印

   - 当右子树非空，入栈

   - 当左子树非空，入栈

## 后序遍历

迂回的方法：先序遍历（但左子树先入栈），再翻转结果

## 统一解法

增加空节点以表示下一个节点是要被操作的节点

```c++
vector<int> preorderTraversal(TreeNode* root)
{
    stack<TreeNode*> sck;
    if (root)
        sck.push(root);
    vector<int> ans;
    while (!sck.empty()) {
        auto top = sck.top();
        sck.pop();
        if (top) {
            if (top->right)
                sck.push(top->right);
            if (top->left)
                sck.push(top->left);
            sck.push(top);
            sck.push(nullptr);
        } else {
            ans.push_back(sck.top()->val);
            sck.pop();
        }
    }
    return ans;
}

vector<int> inorderTraversal(TreeNode* root)
{
    stack<TreeNode*> sck;
    if (root)
        sck.push(root);
    vector<int> ans;
    while (!sck.empty()) {
        auto top = sck.top();
        sck.pop();
        if (top) {
            if (top->right)
                sck.push(top->right);
            sck.push(top);
            sck.push(nullptr);
            if (top->left)
                sck.push(top->left);
        } else {
            ans.push_back(sck.top()->val);
            sck.pop();
        }
    }
    return ans;
}

vector<int> postorderTraversal(TreeNode* root)
{
    stack<TreeNode*> sck;
    if (root)
        sck.push(root);
    vector<int> ans;
    while (!sck.empty()) {
        auto top = sck.top();
        sck.pop();
        if (top) {
            sck.push(top);
            sck.push(nullptr);
            if (top->right)
                sck.push(top->right);
            if (top->left)
                sck.push(top->left);
        } else {
            ans.push_back(sck.top()->val);
            sck.pop();
        }
    }
    return ans;
}
```
