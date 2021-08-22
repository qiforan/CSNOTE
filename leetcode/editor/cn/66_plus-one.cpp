#include <bits/stdc++.h>
using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        reverse(digits.begin(), digits.end());
        int carry = 1;
        for(int i = 0; i < digits.size(); i++){
            if(carry == 0)
                break;
            if(digits[i] < 9){
                digits[i]++;
                carry = 0;
            }
            else
                digits[i] = 0;
        }
        if(carry)
            digits.push_back(1);
        reverse(digits.begin(), digits.end());
        return digits;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given a non-empty array of decimal digits representing a non-negative integer,
// increment one to the integer. 
//
// The digits are stored such that the most significant digit is at the head of 
//the list, and each element in the array contains a single digit. 
//
// You may assume the integer does not contain any leading zero, except the numb
//er 0 itself. 
//
// 
// Example 1: 
//
// 
//Input: digits = [1,2,3]
//Output: [1,2,4]
//Explanation: The array represents the integer 123.
// 
//
// Example 2: 
//
// 
//Input: digits = [4,3,2,1]
//Output: [4,3,2,2]
//Explanation: The array represents the integer 4321.
// 
//
// Example 3: 
//
// 
//Input: digits = [0]
//Output: [1]
// 
//
// 
// Constraints: 
//
// 
// 1 <= digits.length <= 100 
// 0 <= digits[i] <= 9 
// 
// Related Topics 数组 
// 👍 601 👎 0
