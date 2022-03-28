# C++11 新特性

## 1.稳定性与兼容性

### 1.1 兼容 C99

C++11 增加了对 C99 特性的支持。

* 预定义宏
* `__func__` 预定义标识符
* `_Pragma` 操作符
* 不定参数宏
* 宽窄字符串连接

#### 预定义宏

用于检验机器环境对 C 标准和 C 库的支持状况。预定义宏对多平台代码的编写非常重要，通过 `#ifdef` 等预处理指令，可以适配不同平台。

* `__STDC_HOSTED__` 编译器的环境是否包含完整的标准 C 库

* `__STDC__` 编译器的实现是否和 C 标准一致

* `__STDC_VERSION__` C 标准版本

如果用户重定义预定义宏，结果是ub。

#### `__func__`

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

#### `_Pragma`

`#pragma once` 会指示编译器该头文件只编译一次，这与 `_Pragma("once")` 效果一样。

`_Pragma` 操作符的格式如下：

```cpp
_Pragma (字符字面量)
```

`_Pragma` 是一个操作符，故可嵌套在宏里面。

#### `__VA_ARGS__`

变长参数的宏定义是指宏定义中参数列表最后一个为省略号，而 `__VA_ARGS__` 可以替换省略号代表的字符串。

```cpp
#define PR(...) printf(__VA_ARGS__)
```

### 1.2. 长整型

在 C++11 中，标准要求 `long long` 整形可以在不同平台上有不同的长度，但至少有 64 位。在书写数字面量时，可以使用 LL 后缀(或 ll) 标识一个 `long long` 类型的字面量，使用 ULL 表示一个 `unsigned long long` 类型字面量。

```cpp
long long int lli = -9000000000LL;
unsigned long long int ulli = -9000000000000000LL;
```

C++11 有很多与 `long long` 等价的类型。下面的类型是等价的：`long long`, `signed long long`, `long long int`.

对于 `printf` 函数，使用 `%lld` 打印 `long long` 类型变量。

在 `<climits>` 中有 `LLONG_MIN`, `LLONG_MAX` 表示平台上 `long long` 的最小值和最大值。

### 1.3. 版本宏

`__cplusplus` 宏通常被定义为一个整数，随着C++标准变化，该值也会变化，且比以往的值大。

在 C++03 中，`__cplusplus` 为 `199711L`；在 C++11 标准中，该值为 `201103L`。

```cpp
#if __cplusplus < 201103L
    #error "should use C++11 implementation"
#endif
```

如果不支持 C++11 则会立即报错并终止。

### 1.4. 静态断言

在 C++ 中，`<cassert>` 头文件定义了 `assert` 宏，用于运行时断言。可以定义宏 `NDEBUG` 来禁用 `assert` 宏，此时 `assert` 宏会被展开一条无意义的语句。

C++11 引入 `static_assert` ，用于编译器断言，它接受两个参数，一个断言表达式，一个警告信息。

断言表达式必须是在编译器可以计算的表达式，即常量表达式。

### 1.5. `noexcept` 修饰符

`noexcept` 表示其修饰的函数不会抛出异常。如果抛出异常，编译器可以选择直接调用 `std::terminate()` 来终止程序运行。

`noexcept` 语法如下。常量表达式会转换为 bool 类型的值。

```cpp
void excpt_func() noexcept;
void excpt_func() noexcept(常量表达式);
```

`noexcept` 可以保证应用程序的安全，比如一个析构函数不应该抛出异常。C++11 析构函数默认 `noexcept(true)`.

### 1.6. 变量初始化

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

### 1.7. 非静态成员的 sizeof

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

### 1.8. friend 语法

C+++11 中，声明一个类为另一个类的友元时，不需要使用 class 关键字。

这个改动在模板元编程带来好处：可以为类模板声明友元。

### 1.9. final/override

如果派生类在虚函数声明时使用了 `override` 描述符，那么该函数必定重载其基类中的同名函数，否则无法通过编译。这既可提示该函数是重载基类函数，也可以保证该函数没有拼写错误，包括函数名拼写错误、函数参数不匹配。

`final` 可以阻止派生类重载虚函数。

### 1.10. 默认模板参数

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

### 1.11. 外部模板

### 1.12. 局部和匿名类作模板实参

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

## 2. 新特性

### 2.1. 构造函数

#### 继承构造函数

类具有派生性，派生类可以自动获得基类的成员变量和接口(虚函数和纯虚函数)，但是基类的成员函数不能被派生类使用。如果派生类要使用基类的成员函数，可以通过 `using` 声明来完成。

派生类中如果有函数与基类同名，则会[屏蔽基类函数](https://gfjiangly.github.io/C++/派生类与基类的同名函数调用情况.html)。

```cpp
struct Base{
    void f(double i) {cout <<"Base i = " << i << endl; }
};
/// 派生类 `Derived` 实际拥有两个 f 函数。
struct Derived : Base {
    using Base::f;
    void f(int i) {cout <<"Derived i = " << i << endl;}
};
```

C++ 11 中，子类可以通过使用 `using 声明` 来声明继承基类的构造函数。

```cpp
struct A {
    A(int i){}
    A(double d, int i) {}
    A(float f, int i, char* c){}
};

struct B:A {
    using A::A;
}
```

这里通过 `using A::A`, 把基类中的构造函数继承到派生类 `B`.

#### 委托构造函数

C++ 11 允许将一个构造函数设定为 “基准版本”，其他构造函数可以委派该构造函数来初始化。

```cpp
class Info{
public:
    Info() {InitRest();}
    Info(int i) {this->Info(); type = i;}
    Info(char e) {this->Info(); name = e;}
};
```

### 2.2. 右值引用

#### 拷贝构造

拷贝构造函数是一种特殊的构造函数，它在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象。拷贝构造函数通常用于：

* 通过使用另一个同类型的对象来初始化新创建的对象。

* 复制对象把它作为参数传递给函数。

* 复制对象，并从函数返回这个对象。

如果在类中没有定义拷贝构造函数，编译器会自行定义一个。如果类带有指针变量，并有动态内存分配，则它必须有一个拷贝构造函数。

#### 左值、右值与右值引用

C++ 11 中，右值由将亡值(xvalue) 和纯右值(pvalue). 纯右值是 C++ 98 中右值的概念，如非引用返回的函数返回的临时变量值、运算表达式及不跟对象相关联的字面量，如 2,'c' 等都是纯右值。类型转换函数的返回值、lambda 表达式也是右值。

C++ 11 中，右值引用就是对一个右值进行引用的类型。右值引用和左值引用都属于引用类型，都是左值。左值引用是具名变量名的别值，而右值引用是不具名变量的别名。

`T&& b = ReturnRvalue();` 比 `T b = ReturnRvalue();` 会少一次对象的析构和构造(没有 RVO的情况下).

![table 1](../../image/2021-12-26-19-38-47.png)

`<utility>` 中 `std::move()` 强制转化为右值引用。继而可以通过右值引用使用该值。

被 move 的左值生命周期并没有结束，不会立即析构，但不应再使用该值。

#### 完美转发

完美转发指在函数模板内，完全按照参数的类型，将参数传递给函数模板中调用的另一个函数。

```cpp
template<typename T>
void IamForwoding(T&& t) {
    IrunCodeActually(forward(t));
}
```

##### Universal Reference

模板参数中 `T&&` 是一个通用引用。如果传递的是一个左值，那么 T 会推断为左值引用，Param Type 也是左值引用。如果传递的是右值，那么 `T` 是正常的类型，而 Param Type 为 `T&&`.

##### 引用折叠

![c++11_reference_collpsing](../../image/2021-12-28-16-51-27.png)

```cpp
template <typename T>
void baz(T t) {
  T& k = t;
}
int ii = 4;
baz<int&>(ii);
```

这个实例中，T 被显式化为 `int&`, k 的类型为 `int &` 因为发生了引用折叠。

参考:

* [知乎回答：std::move(expr)和std::forward(expr) 疑问](https://www.zhihu.com/question/34544004/answer/59104471)

* [Perfect forwarding and universal references in C++](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/)

### 2.3. 显式转换操作符

`explict` 禁止隐式转换。

```cpp
class ConvertTo{};
class Convertable{
public:
    explicit operator ConvertTo() const {return ConvertTo();}
};
void test()
{
    Convertable c;
    ConvertTo ct(c);
    ConvertTo ct2 = c; // implicit type conversion, fail
    ConvertTo ct3 = static_cast<ConvertTo>(c); // explicit type conversion, success
}
```

### 2.4. 列表初始化

TODO

### 2.5. POD 类型

POD 是 Plain Old Data 的缩写。

### 2.6 SFINEA

### 2.7 decltype

运行时类型识别(RTTI) 的机制是为每个类型产生一个 `type_info` 类型的数据。程序员可以在程序中使用 `typeid` 随时查询一个变量的类型，返回变量相应的 `type_info` 数据。而 `type_info` 的 `name` 成员函数可以返回类型的名字。C++ 11 增加了 `hash_code` 成员函数，返回该类型唯一的哈希值。
