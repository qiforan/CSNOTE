#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        if(digits.size() == 0)
            return vector<string>();
        vector<string> dict({"abc","def", "ghi", "jkl", "mno","pqrs","tuv","wxyz"});
        helper(0,"",digits,dict);
        return ret;
    }

private:
    vector<string> ret;
    void helper(int i , string cur, const string &digits, const vector<string>& dict){
        if(i >= digits.size()){
            ret.push_back(cur);
            return;
        }
        for(int j = 0; j < dict[digits[i] - '2'].size(); j++)
            helper(i+1, cur+dict[digits[i] - '2'][j], digits,dict);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    for(auto str:s.letterCombinations("23"))
        cout << str << " ";
    return 0;
}

//Given a string containing digits from 2-9 inclusive, return all possible lette
//r combinations that the number could represent. Return the answer in any order. 
//
//
// A mapping of digit to letters (just like on the telephone buttons) is given b
//elow. Note that 1 does not map to any letters. 
//
// 
//
// 
// Example 1: 
//
// 
//Input: digits = "23"
//Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
// 
//
// Example 2: 
//
// 
//Input: digits = ""
//Output: []
// 
//
// Example 3: 
//
// 
//Input: digits = "2"
//Output: ["a","b","c"]
// 
//
// 
// Constraints: 
//
// 
// 0 <= digits.length <= 4 
// digits[i] is a digit in the range ['2', '9']. 
// Related Topics 深度优先搜索 递归 字符串 回溯算法 
// 👍 1046 👎 0
