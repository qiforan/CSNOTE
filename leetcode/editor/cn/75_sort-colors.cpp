#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    void sortColors(vector<int> &nums)
    {
        const int n = nums.size();
        vector<int> &v = nums;
        int i = 0, j = n - 1;
        int i_ = i, j_ = j;
        while (i <= j_) {
            if (v[i] == 0)
                swap(v[i], v[i_]);
            else if (v[i] == 2){
                swap(v[i], v[j_--]);
                continue;
            }
            if (v[i_] == 0)
                i_++;
            i++;
        }
        for (int i = 0; i < n; i++)
            printf("%d ", v[i]);

    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    vector<int> v{1,0,2};
    s.sortColors(v);
    return 0;
}

//Given an array nums with n objects colored red, white, or blue, sort them in-p
//lace so that objects of the same color are adjacent, with the colors in the orde
//r red, white, and blue. 
//
// Here, we will use the integers 0, 1, and 2 to represent the color red, white,
// and blue respectively. 
//
// Follow up: 
//
// 
// Could you solve this problem without using the library's sort function? 
// Could you come up with a one-pass algorithm using only O(1) constant space? 
// 
//
// 
// Example 1: 
// Input: nums = [2,0,2,1,1,0]
//Output: [0,0,1,1,2,2]
// Example 2: 
// Input: nums = [2,0,1]
//Output: [0,1,2]
// Example 3: 
// Input: nums = [0]
//Output: [0]
// Example 4: 
// Input: nums = [1]
//Output: [1]
// 
// 
// Constraints: 
//
// 
// n == nums.length 
// 1 <= n <= 300 
// nums[i] is 0, 1, or 2. 
// 
// Related Topics 排序 数组 双指针 
// 👍 735 👎 0
