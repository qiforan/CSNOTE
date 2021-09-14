#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.size() == 0)
            return "";
        const int n = strs.size();
        int pos = 0;
        while (1) {
            char ch = 0;
            bool finish = false;
            for (int i = 0; i < n; i++)
                if (pos > strs[i].size() || (ch > 0 && ch != strs[i][pos])) {
                    finish = true;
                    break;
                } else
                    ch = strs[i][pos];
            if (finish) break;
            pos++;
        }
        return strs[0].substr(0, pos);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<string> strs({"flower", "flow", "flight"});
    cout << s.longestCommonPrefix(strs);
    return 0;
}

//Write a function to find the longest common prefix string amongst an array of 
//strings. 
//
// If there is no common prefix, return an empty string "". 
//
// 
// Example 1: 
//
// 
//Input: strs = ["flower","flow","flight"]
//Output: "fl"
// 
//
// Example 2: 
//
// 
//Input: strs = ["dog","racecar","car"]
//Output: ""
//Explanation: There is no common prefix among the input strings.
// 
//
// 
// Constraints: 
//
// 
// 0 <= strs.length <= 200 
// 0 <= strs[i].length <= 200 
// strs[i] consists of only lower-case English letters. 
// 
// Related Topics 字符串 
// 👍 1387 👎 0
