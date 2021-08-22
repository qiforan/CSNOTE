#include <bits/stdc++.h>
using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if(n <= 0)
            return ret;
        helper(n,n,"");
        return ret;
    }
private:
    vector<string> ret;
    void helper(int l,int r,string cur)
    {
        if(r == 0){
            ret.push_back(cur);
        }
        if(l > 0 )
            helper(l-1,r,cur+"(");
        if(r > l)
            helper(l,r-1,cur + ")");
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given n pairs of parentheses, write a function to generate all combinations of
// well-formed parentheses. 
//
// 
// Example 1: 
// Input: n = 3
//Output: ["((()))","(()())","(())()","()(())","()()()"]
// Example 2: 
// Input: n = 1
//Output: ["()"]
// 
// 
// Constraints: 
//
// 
// 1 <= n <= 8 
// 
// Related Topics 字符串 回溯算法 
// 👍 1485 👎 0
