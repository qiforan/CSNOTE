#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    string intToRoman(int num)
    {
        mp[1] = "I";
        mp[5] = "V";
        mp[10] = "X";
        mp[50] = "L";
        mp[100] = "C";
        mp[500] = "D";
        mp[1000] = "M";
        string ret = "";
        int x = 1000;
        int r = num / x;
        num %= 1000;
        helper(ret, r, x);
        while (num) {
            x /= 10;
            if (num >= x * 9) {
                helper(ret, 1, x);
                helper(ret, 1, x * 10);
                num -= 9 * x;
            }
            if (num >= x * 4) {
                if (num < x * 5) {
                    helper(ret, 1, x);
                    num += x;
                }
                helper(ret, 1, x * 5);
                num -= 5 * x;
            }
            r = num / x;
            helper(ret, r, x);
            num %= x;
        }
        return ret;
    }

private:
    unordered_map<int, string> mp;

    void helper(string &ret, int n, int i)
    {
        while (n--)
            ret += mp[i];
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Roman numerals are represented by seven different symbols: I, V, X, L, C, D an
//d M. 
//
// 
//Symbol       Value
//I             1
//V             5
//X             10
//L             50
//C             100
//D             500
//M             1000 
//
// For example, 2 is written as II in Roman numeral, just two one's added togeth
//er. 12 is written as XII, which is simply X + II. The number 27 is written as XX
//VII, which is XX + V + II. 
//
// Roman numerals are usually written largest to smallest from left to right. Ho
//wever, the numeral for four is not IIII. Instead, the number four is written as 
//IV. Because the one is before the five we subtract it making four. The same prin
//ciple applies to the number nine, which is written as IX. There are six instance
//s where subtraction is used: 
//
// 
// I can be placed before V (5) and X (10) to make 4 and 9. 
// X can be placed before L (50) and C (100) to make 40 and 90. 
// C can be placed before D (500) and M (1000) to make 400 and 900. 
// 
//
// Given an integer, convert it to a roman numeral. 
//
// 
// Example 1: 
//
// 
//Input: num = 3
//Output: "III"
// 
//
// Example 2: 
//
// 
//Input: num = 4
//Output: "IV"
// 
//
// Example 3: 
//
// 
//Input: num = 9
//Output: "IX"
// 
//
// Example 4: 
//
// 
//Input: num = 58
//Output: "LVIII"
//Explanation: L = 50, V = 5, III = 3.
// 
//
// Example 5: 
//
// 
//Input: num = 1994
//Output: "MCMXCIV"
//Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
// 
//
// 
// Constraints: 
//
// 
// 1 <= num <= 3999 
// 
// Related Topics 数学 字符串 
// 👍 465 👎 0
