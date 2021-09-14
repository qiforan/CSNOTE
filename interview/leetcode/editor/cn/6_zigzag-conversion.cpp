#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    string convert(string s, int numRows)
    {
        if(numRows == 1)
            return s;
        const int n = s.size();
        vector<string> sv(numRows, "");
        int dir = 0;
        int pos = 0;
        for (int k = 0; k < n; k++) {
            sv[pos] += s[k];
            if (dir == 0) {
                pos++;
                if (pos >= numRows) {
                    dir = 1;
                    pos -= 2;
                }
            } else {
                pos--;
                if (pos < 0) {
                    dir = 0;
                    pos += 2;
                }
            }
        }
        string ret = "";
        for (auto v: sv)
            ret += v;
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    cout << s.convert("AB", 1);
    return 0;
}

//The string "PAYPALISHIRING" is written in a zigzag pattern on a given number o
//f rows like this: (you may want to display this pattern in a fixed font for bett
//er legibility) 
//
// 
//P   A   H   N
//A P L S I I G
//Y   I   R
// 
//
// And then read line by line: "PAHNAPLSIIGYIR" 
//
// Write the code that will take a string and make this conversion given a numbe
//r of rows: 
//
// 
//string convert(string s, int numRows);
// 
//
// 
// Example 1: 
//
// 
//Input: s = "PAYPALISHIRING", numRows = 3
//Output: "PAHNAPLSIIGYIR"
// 
//
// Example 2: 
//
// 
//Input: s = "PAYPALISHIRING", numRows = 4
//Output: "PINALSIGYAHRPI"
//Explanation:
//P     I    N
//A   L S  I G
//Y A   H R
//P     I
// 
//
// Example 3: 
//
// 
//Input: s = "A", numRows = 1
//Output: "A"
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 1000 
// s consists of English letters (lower-case and upper-case), ',' and '.'. 
// 1 <= numRows <= 1000 
// 
// Related Topics 字符串 
// 👍 941 👎 0
