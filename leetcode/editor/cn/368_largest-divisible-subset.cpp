#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    typedef pair<int, int> pii;

    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        pii max_pii = {1, 0};
        const int n = nums.size();
        vector<pii> dp(n);
        for (int i = 0; i < n; i++) {
            dp[i].first = 1;
            dp[i].second = i;
            for (int j = 0; j < i; j++)
                if (nums[i] % nums[j] == 0 && dp[j].first >= dp[i].first)
                    dp[i] = {dp[j].first + 1, j};
            max_pii = max(max_pii, {dp[i].first,i});
        }
        vector<int> ret;
        for(int i = 0,a=max_pii.second; i < max_pii.first; a = dp[a].second,i++)
            ret.push_back(nums[a]);
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> v{1,2,3};
    s.largestDivisibleSubset(v);
    return 0;
}

//Given a set of distinct positive integers, find the largest subset such that e
//very pair (Si, Sj) of elements in this subset satisfies: 
//
// Si % Sj = 0 or Sj % Si = 0. 
//
// If there are multiple solutions, return any subset is fine. 
//
// Example 1: 
//
// 
// 
//Input: [1,2,3]
//Output: [1,2] (of course, [1,3] will also be ok)
// 
//
// 
// Example 2: 
//
// 
//Input: [1,2,4,8]
//Output: [1,2,4,8]
// 
// 
// Related Topics 数学 动态规划 
// 👍 180 👎 0
