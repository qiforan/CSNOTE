#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        n = nums.size();
        int l = 0;
        sort(nums.begin(), nums.end());
        unordered_set<int> se(nums.begin(), nums.end());
        vector<vector<int>> ret;
        while (l < n && nums[l] <= 0) {
            int r = n - 1;
            while (l < r) {
                int left = -nums[l] - nums[r];
                if (left <= nums[r]) {
                    if (left == nums[r] && l < r - 1 && nums[r] == nums[r - 1])
                        ret.push_back({nums[l], left, left});
                    else if (left < nums[r] && left > nums[l] && se.find(left) != se.end())
                        ret.push_back({nums[l], left, nums[r]});
                    else if (left == nums[l] && l + 1 < r && nums[l + 1] == nums[l])
                        ret.push_back({nums[l], left, nums[r]});
                    r_sub(r, nums);
                } else
                    break;
            }
            l_add(l, nums);
        }
        return ret;
    }

private:
    int n;

    void l_add(int &l, const vector<int> &nums)
    {
        do {
            l++;
        } while (l < n && nums[l] == nums[l - 1]);
    }

    void r_sub(int &r, const vector<int> &nums)
    {
        do {
            r--;
        } while (0 <= r && nums[r] == nums[r + 1]);
    }

};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> v{3, 0, -2, -1, 1, 2};
    s.threeSum(v);
    return 0;
}

//Given an array nums of n integers, are there elements a, b, c in nums such tha
//t a + b + c = 0? Find all unique triplets in the array which gives the sum of ze
//ro. 
//
// Notice that the solution set must not contain duplicate triplets. 
//
// 
// Example 1: 
// Input: nums = [-1,0,1,2,-1,-4]
//Output: [[-1,-1,2],[-1,0,1]]
// Example 2: 
// Input: nums = []
//Output: []
// Example 3: 
// Input: nums = [0]
//Output: []
// 
// 
// Constraints: 
//
// 
// 0 <= nums.length <= 3000 
// -105 <= nums[i] <= 105 
// 
// Related Topics 数组 双指针 
// 👍 2829 👎 0
