#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numDecodings(string s)
    {
        const int n = s.size();
        int dp1 = 0;
        if (validate(s[0]))
            dp1++;
        if (n == 1)
            return dp1;
        int dp2 = 0;
        if (validate(s[1]))
            dp2 += dp1;
        if (validate(s[0], s[1]))
            dp2++;
        if (n == 2)
            return dp2;
//        printf("dp1 = %d, dp2 = %d\n", dp1, dp2);
        for (int i = 2; i < n; i++) {
            int temp = dp2;
            dp2 = 0;
            if (validate(s[i])) {
//                printf("1 pass ");
                dp2 += temp;
            }
            if (validate(s[i - 1], s[i])) {
                dp2 += dp1;
//                printf("2 pass");
            }
            dp1 = temp;
//            printf("dp1 = %d, dp2 = %d\n", dp1, dp2);
        }
        return dp2;
    }

    bool validate(char a, char b)
    {
        if (/*(a == '0' && b > '0') ||*/ a == '1' || (a == '2' && b <= '6'))
            return true;
        return false;
    }

    bool validate(char a)
    {
        return (a > '0' && a <= '9');
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    cout << s.numDecodings("2101");
    return 0;
}

//A message containing letters from A-Z is being encoded to numbers using the fo
//llowing mapping: 
//
// 
//'A' -> 1
//'B' -> 2
//...
//'Z' -> 26
// 
//
// Given a non-empty string containing only digits, determine the total number o
//f ways to decode it. 
//
// The answer is guaranteed to fit in a 32-bit integer. 
//
// 
// Example 1: 
//
// 
//Input: s = "12"
//Output: 2
//Explanation: It could be decoded as "AB" (1 2) or "L" (12).
// 
//
// Example 2: 
//
// 
//Input: s = "226"
//Output: 3
//Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6)
//.
// 
//
// Example 3: 
//
// 
//Input: s = "0"
//Output: 0
//Explanation: There is no character that is mapped to a number starting with '0
//'. We cannot ignore a zero when we face it while decoding. So, each '0' should b
//e part of "10" --> 'J' or "20" --> 'T'.
// 
//
// Example 4: 
//
// 
//Input: s = "1"
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 100 
// s contains only digits and may contain leading zero(s). 
// 
// Related Topics 字符串 动态规划 
// 👍 582 👎 0
