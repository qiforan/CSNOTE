C++11 增加了 `long long` 的支持，要求至少 64 位。在写字面量时，使用 `LL` 后缀标识。

```cpp
long long int lli = -9000000000LL;
```

下面类型是等价的，`long long`, `long long int`, `signed long long int`, `signed long long`.

在 `<climits>` 中查看和 `long long` 相关的宏

* `LLONG_MIN`

* `LLONG_MAX`

* `ULLONG_MIN`