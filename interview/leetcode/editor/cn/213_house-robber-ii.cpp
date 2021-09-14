#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int rob(vector<int> &nums)
    {
        const int n = nums.size();
        if (n == 1)
            return nums[0];
        if (n == 2)
            return max(nums[0], nums[1]);
        else return max(helper(nums, 0, n - 2), helper(nums, 1, n - 1));
    }

private:
    int helper(const vector<int> &v, int s, int e)
    {
        int prev = 0;
        int cur = v[s];
        int cur_bck;
        for (int i = s + 1; i <= e; i++) {
            cur_bck = cur;
            cur = max(prev + v[i], cur);
            prev = cur_bck;
//            printf("prev = %d, cur = %d\n", prev, cur);
        }
        return cur;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> v{1, 3, 1, 3, 100};
    cout << s.rob(v) << endl;
    return 0;
}

//You are a professional robber planning to rob houses along a street. Each hous
//e has a certain amount of money stashed. All houses at this place are arranged i
//n a circle. That means the first house is the neighbor of the last one. Meanwhil
//e, adjacent houses have a security system connected, and it will automatically c
//ontact the police if two adjacent houses were broken into on the same night. 
//
// Given a list of non-negative integers nums representing the amount of money o
//f each house, return the maximum amount of money you can rob tonight without ale
//rting the police. 
//
// 
// Example 1: 
//
// 
//Input: nums = [2,3,2]
//Output: 3
//Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 
//2), because they are adjacent houses.
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,3,1]
//Output: 4
//Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
//Total amount you can rob = 1 + 3 = 4.
// 
//
// Example 3: 
//
// 
//Input: nums = [0]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 100 
// 0 <= nums[i] <= 1000 
// 
// Related Topics 动态规划 
// 👍 435 👎 0
