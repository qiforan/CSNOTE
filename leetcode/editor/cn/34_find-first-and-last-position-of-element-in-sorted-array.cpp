#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        const int n = nums.size();
        return vector<int>({helper1(nums, 0, n - 1, target), helper2(nums, 0, n - 1, target)});
    }

private:
    int helper1(vector<int> &nums, int l, int r, int target)
    {
//        printf("helper1 nums[%d] = %d, nums[%d] = %d \n", l,nums[l],r,nums[r]);
        if(l > r)
            return -1;
        if(l == r){
            if(target == nums[l])
                return l;
            else return -1;
        }
        int mid = (l + r) / 2;
        if (nums[mid] >= target)
            return helper1(nums, l, mid, target);
        else return helper1(nums, mid + 1, r, target);
    }

    int helper2(vector<int> &nums, int l, int r, int target)
    {
//        printf("helper2 nums[%d] = %d, nums[%d] = %d \n", l,nums[l],r,nums[r]);
        if(l > r)
            return -1;
        if(l == r){
        if(target == nums[r])
            return r;
        else return -1;
        }
        int mid = (l + r + 1) / 2;
        if (nums[mid] <= target)
            return helper2(nums, mid, r, target);
        else return helper2(nums, l, mid - 1, target);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> v{5,7,7,8,8,10};
    for(auto e:s.searchRange(v,6))
        cout << e << endl;
    return 0;
}

//Given an array of integers nums sorted in ascending order, find the starting a
//nd ending position of a given target value. 
//
// If target is not found in the array, return [-1, -1]. 
//
// Follow up: Could you write an algorithm with O(log n) runtime complexity? 
//
// 
// Example 1: 
// Input: nums = [5,7,7,8,8,10], target = 8
//Output: [3,4]
// Example 2: 
// Input: nums = [5,7,7,8,8,10], target = 6
//Output: [-1,-1]
// Example 3: 
// Input: nums = [], target = 0
//Output: [-1,-1]
// 
// 
// Constraints: 
//
// 
// 0 <= nums.length <= 105 
// -109 <= nums[i] <= 109 
// nums is a non-decreasing array. 
// -109 <= target <= 109 
// 
// Related Topics 数组 二分查找 
// 👍 775 👎 0
