#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int lengthOfLIS(vector<int> &nums)
    {
        const int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], 1 + dp[j]);
//                test(dp);
        return *max_element(dp.begin(),dp.end());
    }
private:
    void test(const vector<int>& dp)
    {
        for(int i = 0; i < dp.size(); i++)
            printf("dp[%d] = %d ",i,dp[i]);
        printf("\n");
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> v{1,3,6,7,9,4,10,5,6};
    s.lengthOfLIS(v);
    return 0;
}

//Given an integer array nums, return the length of the longest strictly increas
//ing subsequence. 
//
// A subsequence is a sequence that can be derived from an array by deleting som
//e or no elements without changing the order of the remaining elements. For examp
//le, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7]. 
//
// 
// Example 1: 
//
// 
//Input: nums = [10,9,2,5,3,7,101,18]
//Output: 4
//Explanation: The longest increasing subsequence is [2,3,7,101], therefore the 
//length is 4.
// 
//
// Example 2: 
//
// 
//Input: nums = [0,1,0,3,2,3]
//Output: 4
// 
//
// Example 3: 
//
// 
//Input: nums = [7,7,7,7,7,7,7]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 2500 
// -104 <= nums[i] <= 104 
// 
//
// 
// Follow up: 
//
// 
// Could you come up with the O(n2) solution? 
// Could you improve it to O(n log(n)) time complexity? 
// 
// Related Topics 二分查找 动态规划 
// 👍 1223 👎 0
