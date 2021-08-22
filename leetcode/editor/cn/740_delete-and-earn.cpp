#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    typedef pair<int, int> pii;
public:
    int deleteAndEarn(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<pii> v;
        if(nums.empty())
            return 0;
        v.push_back(make_pair(nums[0], 1));
        for (int i = 1; i < nums.size(); i++)
            if (nums[i] == v.back().first)
                v.back().second++;
            else
                v.push_back(make_pair(nums[i], 1));
        int n = v.size();
        vector<int> dp(n + 1, 0);
        dp[1] = v[0].first * v[0].second;
        for (int i = 1; i < n; i++)
            if (v[i].first == v[i - 1].first + 1)
                dp[i + 1] = max(dp[i], dp[i - 1] + v[i].first * v[i].second);
            else
                dp[i + 1] = dp[i] + v[i].first * v[i].second;
        return dp[n];

    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> nums{3,4,2};
    s.deleteAndEarn(nums);
    return 0;
}

//Given an array nums of integers, you can perform operations on the array. 
//
// In each operation, you pick any nums[i] and delete it to earn nums[i] points.
// After, you must delete every element equal to nums[i] - 1 or nums[i] + 1. 
//
// You start with 0 points. Return the maximum number of points you can earn by 
//applying such operations. 
//
// Example 1: 
//
// 
//Input: nums = [3, 4, 2]
//Output: 6
//Explanation: 
//Delete 4 to earn 4 points, consequently 3 is also deleted.
//Then, delete 2 to earn 2 points. 6 total points are earned.
// 
//
// 
//
// Example 2: 
//
// 
//Input: nums = [2, 2, 3, 3, 3, 4]
//Output: 9
//Explanation: 
//Delete 3 to earn 3 points, deleting both 2's and the 4.
//Then, delete 3 again to earn 3 points, and 3 again to earn 3 points.
//9 total points are earned.
// 
//
// 
//
// Note: 
//
// 
// The length of nums is at most 20000. 
// Each element nums[i] is an integer in the range [1, 10000]. 
// 
//
// 
// Related Topics 动态规划 
// 👍 213 👎 0
