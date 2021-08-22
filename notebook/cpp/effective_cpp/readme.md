# Effective C++ 笔记

## 术语

**声明式(declaration)** 告诉编译器名称和类型，略去细节。 函数的声明揭示了其签名，包括其参数和返回值。

**定义式(definition)** 提供了声明里遗漏的细节，并分配内存。对函数而言，定义提供了代码本体。

**初始化(initilazation)** 给对象赋初值。

声明和定义可以同时进行。

## 条款 2

由 `define` 定义的常量会在预处理时替换，不会进入记号表（symbol table)，不利于调试。解决方式是用常量替换：

```c++
const double AspectRatio = 1.653;
```

注意：

1. 定义常量指针时，要将指针声明为 `const`.

```c++
const char* const authorName = "Scott Meyers"
```

2. 若为 class 内的常量，应设置为 `static`, 保证只有一个实体。 

关于 `NumTurns` 的疑问，参考:

- [How do I define an in-class constant?](https://www.stroustrup.com/bs_faq2.html#in-class)

- [What is the difference between a definition and a declaration?](https://stackoverflow.com/questions/1410563/what-is-the-difference-between-a-definition-and-a-declaration)

- [why static const int NumTurns = 5; is not a definition?](https://stackoverflow.com/questions/34629876/why-is-declaration-and-definition-defined-this-way-in-effective-c)

一个属于枚举类型(enumerated type) 的数值可充当 `ints` 使用，但无法被取地址，如果不想指针指向你的整数常量，可使用 	`enum`.

如果你想获得 `define` 实现宏的效果（减少函数调用），可以使用 `template inline`.

## 条款 3

`const` 可以修饰全局变量，也可以修饰文件、函数等。

如果 `const` 修饰指针变量，则

- `const` 出现在星号左边，表示被指物是常量；

- `const` 出现在星号右边，表示指针自身是常量，其指向不可变；

令函数返回一个常量，可以减少不恰当使用造成的问题，如错把 `==` 当 `=`.

把某些成员函数限定为 `const`, 一来更易理解函数的含义，二来通过“操作 const 对象”可以改善代码效率，参考条款 20.

添加 `const` 属性重载，包括给参数添加 `const`.

## 条款 5

一个类必须有默认构造函数、拷贝构造函数、赋值构造函数、析构函数，如果没有显式声明，编译器会隐式声明，且都是 public & inline.

编译器生成的默认构造函数和析构函数调用基类构造函数、non-static 成员变量的构造函数或析构函数。