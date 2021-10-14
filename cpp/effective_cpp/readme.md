# Effective C++ 笔记

## 术语

**声明式(declaration)** 告诉编译器名称和类型，略去细节。 函数的声明揭示了其签名，包括其参数和返回值。

**定义式(definition)** 提供了声明里遗漏的细节，并分配内存。对函数而言，定义提供了代码本体。

**初始化(initilazation)** 给对象赋初值。

声明和定义可以同时进行。

## 条款 1

C++ 是一个多重范型编程语言，支持过程形式、面向对象形式、函数形式、范型形式、元编程形式的语言。


## 条款 2

由 `define` 定义的常量会在预处理时替换，不会进入记号表（symbol table)，不利于调试。

解决方式是用 `const` 常量替换：

```c++
const double AspectRatio = 1.653;
```

`const` 对象默认仅在文件内有效。

**注意**：

1. 由于常量定义式被放在头文件内，因此定义常量指针时，要将指针声明为 `const`.

```c++
const char* const authorName = "Scott Meyers"
```

2. 若为 class 内的常量，应设置为 `static`, 保证只有一个实体。 

```cpp
class GamePlayer {
private:
    static const int NumTurns = 5; // 常量声明式，可以不需要定义式
    int socres[NumTurns];          // 使用该常量
    ...
}
```

对于 `static` 且为整型的类变量，如上面的 `NumTurns`，可以不需要提供定义式。

关于 `NumTurns` 的疑问，参考:

- [How do I define an in-class constant?](https://www.stroustrup.com/bs_faq2.html#in-class)

- [What is the difference between a definition and a declaration?](https://stackoverflow.com/questions/1410563/what-is-the-difference-between-a-definition-and-a-declaration)

- [why static const int NumTurns = 5; is not a definition?](https://stackoverflow.com/questions/34629876/why-is-declaration-and-definition-defined-this-way-in-effective-c)

- [Why is declaration and definition defined this way in Effective C++?](https://stackoverflow.com/questions/34629876/why-is-declaration-and-definition-defined-this-way-in-effective-c)

一个属于枚举类型(enumerated type) 的数值可充当 `ints` 使用，但无法被取地址，如果不想指针指向你的整数常量，可使用 	`enum`.

>一个属于枚举类型的数值可充当 `ints` 使用。

```cpp
class GamePlayer {
private:
    enum {NumTurns = 5};           // 
    int socres[NumTurns];          // 使用该常量
    ...
}
```

如果你想获得 `define` 实现宏的效果（减少函数调用），可以使用 `template inline`.

## 条款 3

`const` 可以修饰全局变量，也可以修饰文件、函数等。

如果 `const` 修饰指针变量，则

- `const` 出现在星号左边，表示被指物是常量；

- `const` 出现在星号右边，表示指针自身是常量，其指向不可变；

令函数返回一个常量，可以减少不恰当使用造成的问题，如错把 `==` 当 `=`.

把某些成员函数限定为 `const`, 一来更易理解函数的含义，二来通过“操作 const 对象”可以改善代码效率，参考 条款 20.

添加 `const` 属性可以导致重载，包括给参数添加 `const`.


## 条款 4 构造函数与初始化

永远在使用对象之前初始化。对于内置类型，需要手工完成。对于对象，确保构造函数将对象每一个成员初始化。

构造函数中，容易混淆 **赋值** 和 **初始化**.

对象成员非内置类型变量的初始化动作发生在进入构造函数本体 **之前**。

一个较好的写法是，使用 `member initialization list` 替换赋值动作。

C++ 成员初始化次序比较固定：

1. `base classes` 早于 `derived classes` 被初始化。
2. class 的成员变量总是以其声明的顺序被初始化。

static 对象生命周期从构造出来开始直至程序结束。这种对象包括 global 对象，定义于 namespace 作用域内的对象、在 classes 内、在函数内、在 file 作用域内被声明为 `static` 的对象。其中，函数内的 static 对象被称为 `local static 对象`，其他被称为 `non-local static 对象`.



## 条款 5

一个类必须有默认构造函数、拷贝构造函数、赋值构造函数、析构函数，如果没有显式声明，编译器会隐式声明，且都是 public & inline.
编译器生成的默认构造函数和析构函数调用基类构造函数、non-static 成员变量的构造函数或析构函数。