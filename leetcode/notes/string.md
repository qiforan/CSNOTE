# 字符串操作

## 前缀函数定义

给定一个长度为 $n$ 的字符串 ，其 **前缀函数** 被定义为一个长度为 $n$ 的数组 $\pi$. 
简单来说 $\pi[i]$ 就是，子串 $s[0 \dots i]$ 最长的相等的真前缀与真后缀的长度。特别地，规定 $\pi[0] = 0$.

假设相等的真前缀和后前缀按长度从大到小为：$\pi[i]$, $j^{(1)}$, $j^{(2)}$, $\dots$, $j^{(n)}$, 有 $j^{(n)} = \pi{[j^{(n-1)}-1]}$.

计算前缀函数的函数：

```cpp
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
```