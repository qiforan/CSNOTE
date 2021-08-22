#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    string longestPalindrome(string s)
    {
        const int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        string ret = "";
        for (int i = 1; i <= n; i++) {
            for (int j = 0; i + j - 1 < n; j++) {
                // length is 1
                if (i == 1)
                    dp[j][j + i - 1] = 1;
                    // length is 2
                else if (i == 2) {
                    if (s[j] == s[i + j - 1])
                        dp[j][i + j - 1] = 1;
                    //length greater than 2
                } else {
                    if (s[j] == s[i + j - 1] && dp[j + 1][j + i - 2] == 1)
                        dp[j][i + j - 1] = 1;
                }
//                printf("dp[%d][%d] = %d\n",j,i+j-1,dp[j][i + j - 1]);
                if (dp[j][i + j - 1] && ret.size() < i)
                    ret = s.substr(j, i);
            }
        }
        return ret;
    }

};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    cout << (new Solution)->longestPalindrome("aba") << endl;
    cout << (new Solution)->longestPalindrome("cbbd") << endl;
    cout << (new Solution)->longestPalindrome("aaaa") << endl;
    return 0;
}
