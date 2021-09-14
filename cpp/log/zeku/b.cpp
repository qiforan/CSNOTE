

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * Convert the input string into an interger.
     * @param str string字符串 input string, only decimal num can be accepted.
     * @return int整型
     */
    int atoi_(string str)
    {
        // write code here
        int isNegative = false;
        int isError = false;
        int i = 0;
        // string is null
        if (str.length() == 0)
            return -1;
        // if start with sign
        if (str[0] == '+' || str[0] == '-') {
            // if only has sign
            if (str.length() == 1)
                return -1;
            if (str[0] == '-')
                isNegative = true;
            i = 1;
        }
        long long val = 0;
        // if start with 0
        if (str[i] == '0')
            val = str[i++] - '0';
        for (; i < str.length() && !isError; i++) {
            if (str[i] <= '9' && str[i] > '0') {
                val = val * 10 + (str[i] - '0');
            } else if (str[i] == '0') {
                if (val > 0)
                    val *= 10;
                else
                    isError = true;
            } else
                isError = true;
        }
        // exced
        if (isNegative)
            val *= -1;
        if (val > INT_MAX || val < INT_MIN)
            return -1;
        if (isError)
            return -1;
        return val;
    }
};