# 稳定性与兼容性

## 1. 兼容 C99

C++11 增加了对 C99 特性的支持。

* 预定义宏
* `__func__` 预定义标识符
* `_Pragma` 操作符
* 不定参数宏
* 宽窄字符串连接

### 1.1. 预定义宏

用于检验机器环境对 C 标准和 C 库的支持状况。预定义宏对多平台代码的编写非常重要，通过 `#ifdef` 等预处理指令，可以适配不同平台。

* `__STDC_HOSTED__` 编译器的环境是否包含完整的标准 C 库

* `__STDC__` 编译器的实现是否和 C 标准一致

* `__STDC_VERSION__` C 标准版本

如果用户重定义预定义宏，结果是ub。

### 1.2. `__func__`

返回所在函数的名字。

```cpp
/// 打印 hello,world
#include <iostream>
using namespace std;
const char* hello() { return __func__; };
const char* world() { return __func__; }
int main() {
  cout << hello() << ", " << world() << endl;
  return 0;
}
```

甚至可在构造函数初始化中，使用 `__func__` 初始化成员列表。

### 1.3. `_Pragma`

`#pragma once` 会指示编译器该头文件只编译一次，这与 `_Pragma("once")` 效果一样。

`_Pragma` 操作符的格式如下：

```cpp
_Pragma (字符字面量)
```

`_Pragma` 是一个操作符，故可嵌套在宏里面。

### 1.4. `__VA_ARGS__`

变长参数的宏定义是指宏定义中参数列表最后一个为省略号，而 `__VA_ARGS__` 可以替换省略号代表的字符串。

```cpp
#define PR(...) printf(__VA_ARGS__)
```

## 2. 长整型

在 C++11 中，标准要求 `long long` 整形可以在不同平台上有不同的长度，但至少有 64 位。在书写数字面量时，可以使用 LL 后缀(或 ll) 标识一个 `long long` 类型的字面量，使用 ULL 表示一个 `unsigned long long` 类型字面量。

```cpp
long long int lli = -9000000000LL;
unsigned long long int ulli = -9000000000000000LL;
```

C++11 有很多与 `long long` 等价的类型。下面的类型是等价的：`long long`, `signed long long`, `long long int`.

对于 `printf` 函数，使用 `%lld` 打印 `long long` 类型变量。

在 `<climits>` 中有 `LLONG_MIN`, `LLONG_MAX` 表示平台上 `long long` 的最小值和最大值。

## 3. 宏 `__cplusplus`

`__cplusplus` 宏通常被定义为一个整数，随着C++标准变化，该值也会变化，且比以往的值大。

在 C++03 中，`__cplusplus` 为 `199711L`；在 C++11 标准中，该值为 `201103L`。

```cpp
#if __cplusplus < 201103L
    #error "should use C++11 implementation"
#endif
```

如果不支持 C++11 则会立即报错并终止。

## 4. 静态断言

在 C++ 中，`<cassert>` 头文件定义了 `assert` 宏，用于运行时断言。可以定义宏 `NDEBUG` 来禁用 `assert` 宏，此时 `assert` 宏会被展开一条无意义的语句。

C++11 引入 `static_assert` ，用于编译器断言，它接受两个参数，一个断言表达式，一个警告信息。

断言表达式必须是在编译器可以计算的表达式，即常量表达式。

## 5. `noexcept` 修饰符

`noexcept` 表示其修饰的函数不会抛出异常。如果抛出异常，编译器可以选择直接调用 `std::terminate()` 来终止程序运行。

`noexcept` 语法如下。常量表达式会转换为 bool 类型的值。

```cpp
void excpt_func() noexcept;
void excpt_func() noexcept(常量表达式);
```

`noexcept` 可以保证应用程序的安全，比如一个析构函数不应该抛出异常。C++11 析构函数默认 `noexcept(true)`.

## 6. 变量初始化

C++ 类中 **静态成员变量** 如果是常量且是整型或者枚举型，可以在类内初始化。

```cpp
class Init{
private:
  const static int b = 0; // valid
  int c = 1;              // invalid
  static int d = 0;       // invalid
  static const double e = 1.3; //invalid
};
```

C++11 允许使用等号或花括号进行非静态成员变量初始化，称之为就地初始化。

```cpp
struct init {
  int a = 1;
  double b {1,2};
};
```

如果一个类既有就地初始化，也有成员列表初始化，则初始化列表初始化变量的效果要优于就地初始化。

## 7. 非静态成员的 sizeof

在 C++98 中，对非静态成员变量使用 `sizeof` 操作是非法的，而在 C++11 中，是合法的。

```cpp
class A{
  int a;
  static int b;
};
A a;
cout << sizeof(a.a) << endl; // C++98 valid, C++11 valid
cout << sizeof(A::b) << endl; // C++98 & C++11 valid
cout << sizeof(A::a) << endl; // C++98 invalid, C++11 valid
```

在 C++98 中，在没有定义类实例时，要获得类成员的大小，需要这样做:

```cpp
sizeof(((A*)0)->a);
```

## 8. friend 语法

C+++11 中，声明一个类为另一个类的友元时，不需要使用 class 关键字。

这个改动在模板元编程带来好处：可以为类模板声明友元。

## 9. final/override

如果派生类在虚函数声明时使用了 `override` 描述符，那么该函数必定重载其基类中的同名函数，否则无法通过编译。这既可提示该函数是重载基类函数，也可以保证该函数没有拼写错误，包括函数名拼写错误、函数参数不匹配。

`final` 可以阻止派生类重载虚函数。

## 10. 默认模板参数

C++11 允许模板声明时有默认参数。

```cpp
template<class T, class U = double>
void f(T t =0, U u = 0);
void g() {
  f(1,'c'); // f<int,char>(1,'c');
  f(1);     // f<int, double>(1,0);
  f();      // invalid
  f<int>(); // f<int,double>(0,0);
}
```

## 11. 外部模板

## 12. 局部和匿名类作模板实参

C++ 11 允许局部类和匿名类作为模板参数

```cpp
template<typename T> class X {};
struct A{} a;
typedef struct {int i;} B; // B 是匿名类型

void Fun() {
  struct C {} c;  // C 是局部类型
  X<A> x1;        // C++98 & C++11 valid
  X<B> x2;        // C++98 invalid, C++11 valid
  X<C> x2;        // C++98 invalid, C++11 valid
}
```
