#include <bits/stdc++.h>
using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int reverse(int x) {
        int flag = 0;
        if(x < 0)
            flag = 1;
        string s = to_string(abs(x));
        std::reverse(s.begin(),s.end());
        long long ret = 0;
        for(int i = 0; i < s.size(); i++)
            ret = ret*10 + s[i] - '0';
        if(ret > INT_MAX)
            return 0;
        return flag ? -1 * ret : ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    s.reverse(1534236469);
    return 0;
}

//Given a 32-bit signed integer, reverse digits of an integer. 
//
// Note: 
//Assume we are dealing with an environment that could only store integers withi
//n the 32-bit signed integer range: [−231, 231 − 1]. For the purpose of this prob
//lem, assume that your function returns 0 when the reversed integer overflows. 
//
// 
// Example 1: 
// Input: x = 123
//Output: 321
// Example 2: 
// Input: x = -123
//Output: -321
// Example 3: 
// Input: x = 120
//Output: 21
// Example 4: 
// Input: x = 0
//Output: 0
// 
// 
// Constraints: 
//
// 
// -231 <= x <= 231 - 1 
// 
// Related Topics 数学 
// 👍 2408 👎 0
