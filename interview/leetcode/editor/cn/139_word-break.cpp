#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        dp.resize(s.size(),-1);
        for_each(wordDict.begin(), wordDict.end(),[this](const string& str){max_len = max(max_len,(int)str.size());});
        set<string> se(wordDict.begin(), wordDict.end());
        bool flag = false;
        helper(s,0,flag, se);
        return flag;
    }

private:
    int max_len = 0;
    vector<int> dp;
    void helper(const string &s, int i, bool& flag,const set<string> & se)
    {
        if(i >= s.size())
            flag = true;
        if(flag || dp[i] != -1)
            return;
        dp[i] = 0;
        for(int k = 1; k <= max_len; k++){
            if(se.find(s.substr(i,k)) != se.end())
                helper(s,i+k,flag,se);
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    string str = "leetcode";
    vector<string> wordDict({"leet","code"});
    cout << s.wordBreak(str,wordDict) << endl;
    return 0;
}

//Given a non-empty string s and a dictionary wordDict containing a list of non-
//empty words, determine if s can be segmented into a space-separated sequence of 
//one or more dictionary words. 
//
// Note: 
//
// 
// The same word in the dictionary may be reused multiple times in the segmentat
//ion. 
// You may assume the dictionary does not contain duplicate words. 
// 
//
// Example 1: 
//
// 
//Input: s = "leetcode", wordDict = ["leet", "code"]
//Output: true
//Explanation: Return true because "leetcode" can be segmented as "leet code".
// 
//
// Example 2: 
//
// 
//Input: s = "applepenapple", wordDict = ["apple", "pen"]
//Output: true
//Explanation: Return true because "applepenapple" can be segmented as "apple pe
//n apple".
//             Note that you are allowed to reuse a dictionary word.
// 
//
// Example 3: 
//
// 
//Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
//Output: false
// 
// Related Topics 动态规划 
// 👍 785 👎 0
