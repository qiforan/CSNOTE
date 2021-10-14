C++11 增加了对 C99 特性的支持。

## 1. 预定义宏

* `__STDC_HOSTED__` 编译器的环境是否包含完整的标准 C 库

* `__STDC__` 编译器的实现是否和 C 标准一致

* `__STDC_VERSION__` C 标准版本

如果用户重定义预定义的宏，结果是未知的。

## 2. `__func__`

返回函数所在的位置。

```cpp
#include <iostream>
using namespace std;
const char* hello() { return __func__; };
const char* world() { return __func__; }
int main() {
  cout << hello() << ", " << world() << endl;
  return 0;
}
```

甚至可以在结构体构造函数初始化中，使用 `__func__` 初始化成员列表。

## 3. `_Pragma`

```cpp
Pragma (字符字面量)
```

## 4. `__VA_ARGS__`

变长参数的宏定义是指宏定义中参数列表最后一个为省略号，而 `__VA_ARGS__` 可以替换省略号代表的字符串。

```cpp
#define PR(...) printf(__VA_ARGS__)
```