#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxProduct(vector<int> &nums)
    {
        int ret = INT_MIN;
        int mx = 1;
        int mn = 1;
        for (auto num:nums) {
            int mx_ = mx;
            mx = max(num, max(mx*num,mn*num));
            mn = min(num, min(mx_*num,mn*num));
//            printf("mx = %d, mn = %d\n",mx,mn);
            ret = max(mx,ret);
        }
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector v{-4,-3,-2};
    cout << s.maxProduct(v);
    return 0;
}

//Given an integer array nums, find the contiguous subarray within an array (con
//taining at least one number) which has the largest product. 
//
// Example 1: 
//
// 
//Input: [2,3,-2,4]
//Output: 6
//Explanation: [2,3] has the largest product 6.
// 
//
// Example 2: 
//
// 
//Input: [-2,0,-1]
//Output: 0
//Explanation: The result cannot be 2, because [-2,-1] is not a subarray. 
// Related Topics 数组 动态规划 
// 👍 868 👎 0
