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

使用 `const` 常量：

```cpp
const double AspectRatio = 1.653;
```

`const` 对象默认仅在文件内有效。

**注意**：

1. 由于常量定义式被放在头文件内，因此定义常量指针时，要将指针声明为 `const`.

```cpp
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

一个属于枚举类型(enumerated type) 的数值可充当 `ints` 使用，但无法被取地址，如果不想指针指向你的整数常量，可使用  `enum`.

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

## 条款 3 尽可能使用 `const`

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

## 条款 5 默认生成的构造函数

一个类必须有 `默认构造函数`、`copy 构造函数`、`copy 赋值操作符`、`析构函数`. 如果没有显式声明，编译器会隐式声明，且都是 `public & inline`.

编译器生成的默认构造函数或析构函数只会调用基类构造函数或析构函数、non-static 成员变量的构造函数或析构函数。

对于 copy 构造函数和 copy 赋值操作符，编译器创建的版本只是把来源对象中的每一个 non-static 成员变量拷贝到目标对象。

编译器构造出来的  copy 赋值操作符需合法且有意义。如果一个类的成员有引用的话，则需要自定义 copy 赋值操作符。

## 条款 6 拒绝编译器生成的函数

为了阻止编译器自动生成的函数（条款 5），可以手动将其声明为 `private` 并不予实现。也可以 private 继承 `Uncopyable`.

## 条款 7 基类析构函数为 virtual

当 derived class 对象由一个 base class 指针删除时，如果 base class 的析构函数为 non-virtual，其行为是未定义的，即可能 对象中 derived 成分没有被销毁，造成资源泄露。

解决办法:

设置 base class 析构函数为 virtual。

注意：

将所有 class 的析构函数声明为 virtual 是错误的，这会增大 class 的体积。常见的做法是，当 class 内至少含一个 virtual 函数，才声明 virtual 析构函数。

给 base class 一个 virtual 析构函数只适用 polymorphic base class 身上。

## 条款 8 析构函数与异常

析构函数最好不要抛出异常。原因：

1. 抛出异常后的代码不会执行，可能会造成资源泄露。

2. 在异常的传播过程中进行栈展开。在栈展开的过程中就会调用已经在栈构造好的对象的析构函数来释放资源，此时若其他析构函数本身也抛出异常，则前一个异常尚未处理，又有新的异常，会造成程序崩溃。

解决办法：

1. 如果异常出现在析构函数里，应该捕捉异常，而不是抛出异常。

2. 异常处理应该出现在普通函数而非析构函数。

## 条款 9 构造函数和析构函数不调用 virtual 函数

- 不要在构造函数中调用虚函数的原因：因为父类对象会在子类之前进行构造，此时子类部分的数据成员还未初始化， 因此调用子类的虚函数是不安全的，故而C++不会进行动态联编。

- 不要在析构函数中调用虚函数的原因：析构函数是用来销毁一个对象的，在销毁一个对象时，先调用子类的析构函数，然后再调用基类的析构函数。所以在调用基类的析构函数时，派生类对象的数据成员已经“销毁”，这个时再调用子类的虚函数已经没有意义了。

## 条款 10 `operator =` 返回 reference to *this

为了实现 **连锁赋值**，赋值操作符必须返回一个 reference 指向操作符的左侧实参。

```cpp
class Widget {
    Widget& operator=(const Widget& rhs)
    {
        ...
        return *this;
    }
    ...
};
```

[c++中有些重载运算符为什么要返回引用？](https://www.zhihu.com/question/22821783)

## 条款 11 `operator=` 处理自我赋值

自我赋值可能出现问题

```cpp
class Bitmap {...};
class Widget {
    Bitmap *pb;
};
Widget& Widget::operator=(const Widget &rhs)
{
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}
```

如果 `*this` 和 `rhs` 是同一个对象，就会出现指针指向一个被删除的对象。

解决办法：

```cpp
if(this == &rhs) return *this; // 证同测试，identity test
```

这样只解决了部分问题：不是异常安全的，如果 `new` 发生了异常，指针仍指向一块被删除的对象。

调换 `new` 和 `delete` 的先后顺序可以解决问题，唯一的问题是如果 `*this` 和 `rhs` 相同时会有效率问题。

## 条款 12 复制对象勿忘了每一个成分

手动实现 copy 复制构造函数时，不要忘了每一个成分：当添加一个成员变量时，同时修改函数。如果忘记，编译器并不会提醒你。

不要忘记复制 base class 的成分。

## 条款 13 对象管理资源

把资源放入对象中，便可以倚赖 **析构函数** 自动调用机制确保资源被释放。

两个常用的 RAII classes 是 `shared_ptr` 和 `unique_ptr`。

## 条款 14 资源管理类小心 copy

处理 RAII 类的复制，一般有两种情况：

1. 禁止复制

2. 使用引用计数

## 条款 15 RAII 类应该提供对原始资源的访问接口

许多 API 直接处理原始资源，因此需要将 RAII 对象转换为原始资源。

显示转换：提供 `get()` 函数。

隐式转换：重载操作符（`*`,`->`,`conversion operator`)。

[what is operator class_name() const?](https://stackoverflow.com/questions/19666392/what-is-operator-class-name-const)

显式转换较为麻烦，隐式转换可能会增加错误发生的机会。

## 条款 16 delete 要和 new 匹配

删除指针所指空间除了会归还空间，会先调用析构函数。

被删除的指针可能指向单个对象，也可能指向对象数组。

```cpp
delete obj1; // delete one object
delete [] obj2; // delete object array.
```

如果对数组形式做 `typedef` 动作尤为要注意。

## 条款 17 独立语句将 newed 对象放置智能指针

```cpp
processWidget(shared_ptr<Widget>(new Widget), priority());
```

C++ 并无规定参数执行顺序，以上语句可能有如下顺序：

1. 执行 `new Widget`
2. 执行 `priority()`
3. 调用 `shared_ptr` 构造函数

如果 2 中发生异常，3执行不了，就会造成资源泄露。

解决办法：

拆分语句，手动确定上述顺序

```cpp
int priority = priority();
processWidget(shared_ptr<Widget>(new Widget), priority);
```

## 条款 18 接口设计

接口应易于使用。

```cpp
Date(int month, int day, int year);
Date(const Month& month, const Day& day, const Year& year);
```

前者至少有两个问题，容易以错误次序传递参数；容易传递无效参数。

可以通过导入新类型预防此类问题，如后者。

预防客户端错误的另一个方法是限制类型内什么事可做，什么不可做。常见的限制是加上 `const`.

**避免类型的行为与内置类型不一致**，除非有不得不做的理由。

## 条款 19 设计 class

规范：

- 对象如何创建和销毁

- 初始化和赋值的区别

- `passed by value` 意味着什么

- 什么是新 type 的合法值

- 需要继承吗

- 与其他类型之间的转换

- 需要什么样的操作符和函数

- 哪些函数是不需要的（设为 private)

- 一般化，是否需要 `template`

## 条款 20 `pass-by-reference-to-const`

`pass-by-reference-to-const` 方式效率较高，因为没有任何新对象被创建。`const` 保证传入的参数不被改变。

当把一个派生类对象赋给一个基类对象时，会发生 **对象切割**。当一个 `derived class` 对象以 by value 方式传递并视为一个 `base class` 对象时，`base class` 的 copy 构造函数会被调用，`derived class`部分会被切割掉。

传引用可以避免对象切割问题。

对于内置类型、STL的迭代器和函数对象，`pass-by-value` 比较适当。

>大部分迭代器都是比较小的，复制构造函数一般也只是平凡复制，复制开销并不大，反倒传引用因为经常需要间接访问所以影响性能。

## 条款 21 函数返回引用

函数盲目地返回引用可能会导致程序错误或内存泄露。

将一个函数内部的变量（on stack)通过传引用的方式返回会导致函数返回前变量已经析构。

在 heap 新建变量并返回引用，容易忘记析构，造成内存泄露。

## 条款 22 成员变量私有化

将成员变量设置为 `private` 可以更精确地控制对成员变量的访问。

```cpp
class AccessLevels {
public:
    int getReadOnly() const { return readOnly;}
    void setReadWrite(int value) { readWrite = value;}
    int getReadWrite() const { return readWrite;}
    void setWriteOnly(int value) { writeOnly = value;}
private:
    int noAccess;
    int readOnly;
    int readWrite;
    int writeOnly;
}
```

通过函数来访问成员变量，日后可以改变成员变量而不会对 class 的使用者造成影响。

## 条款 23 non-member、non-friend 函数替换 member 函数

在许多方面，member 函数带来的封装性低于 non-member 函数。

## 条款 24 若所有参数皆需要类型转换，采用 non-member 函数

考虑以下代码

```cpp
class Rational {
public:
    // 允许隐式转换
    Rational(int numerator, int denominator = 1);
    int numerator() const { return numerator_; }
    int denominator() const { return denominator_;}
private:
    ...
};
```

如果想要支持 `Rational` 类型的乘法。可能会考虑以下代码

```cpp
class Rational {
    ...
    const Rational operator*(const Rational& rhs) const;
};
```

但是，这个乘法不支持 `2 * a` 的形式。正确的方式是定义一个 non-member 函数

```cpp
const Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}
```

**请记住**：如果你需要为某个函数的所有参数提供类型转换，那么你应该使用 non-member 函数。

## 条款 25 考虑写一个不抛异常的 `swap`

TODO

## 条款 26 尽可能延后变量定义的时间

变量定义可能会有构造函数和析构函数的成本。或许你认为你不可能定义一个不使用的变量，但须考虑到异常。

还要尽可能减少构造函数的开销，比如先构造再赋值不如直接用值构造。

## 条款 27 尽量减少转型

C++ 提供四种新式转型：

```cpp
const_cast<T>(expression)
dynamic_cast<T>(expression)
reinterpret_cast<T>(expression)
static_cast<T>(expression)
```

- cosnt_cast 移除变量的常量特性.T必须是指针或引用。
- dynamic_cast  在执行期进行多态类(有虚函数)之间的转换,用于运行时类型识别.T必须是指针或引用,expression必须返回多态类类型.。它是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作。
- reinterpret_cast 变量二进制位层次上的重新解释,并没有对变量的二进制储存方式进行更改.T 必须是指针,引用或算术类型。
- static_cast 可以执行大多数类型的转换。但与 const_cast 类型相比,static_cast 不能去除 const 或 volatile 属性,与 dynamic_cast 相比不支持运行时类型识别,与 reinterpret_cast 相比不是位层次上的重新解释,而是对位进行改变后的重新编码.

## 条款 28 避免返回 handle 指向对象内部成分



## 条款 30 了解 `inline`

Inline 函数看起来像函数，动作像函数，比宏好得多，调用时没有函数调用时额外开销。inline 函数的观念是，“对函数的每个调用”都以函数本体替换之。这样可能增加代码的大小。

`inline` 造成的代码膨胀会导致额外的换页行为，降低 cache 的命中率，带来效率损失。

但如果 `inline` 函数的本体很小，将函数 inlining 可能会导致更小的代码和更高的 cache 命中率。

`inline` 只是一个申请，编译器不一定响应。大部分编译器拒绝 `inline` 太过复杂的函数。

`inline` 对 virtual 函数无效。

某个类的构造函数看起来是空的，使用 inline 合适，其实是错误的想法；
C++的对象在被创建和销毁时：创建一个对象，每个 base class 及每个成员会自动构造；销毁一个对象时，反向进行析构及销毁；如果遇到异常，编译器尝试的模板代码更多；一旦被 inlined，所有子类都要插入 base class 构造函数的所有自动生成的代码，急速膨胀。

inline 函数无法随着程序库的升级而升级。如果重写了 inline 函数，必须重写编译。

## 条款 48 初涉模板元编程

模板元编程(TMP) 是编写 template-based C++ 程序并执行于编译期的过程。

模板元编程使得某些困难甚至不可能的事情变得容易。由于模板元编程执行于 C++ 编译期，因此可以将某些运行期才能检测到的错误提前检测出来。另外，使用模板元编程的 C++ 程序有较小的可执行文件、较短的运行期、较少的内存需求。缺点是增加了编译时间。

## 条款 49 了解 new-handler

当 `operator new` 无法进行内存分配，就会抛异常。在抛异常前，会调用错误处理函数，`new_handler`。客户可以通过调用 `set_new_handler` 定制这个函数。

```cpp
namespace std {
    typedef void (*new_handler)();
    new_handler set_new_handler(new_handler p) throw();
}
```

`set_new_handler` 的参数是一个指针，指向无法分配足够内存时调用的函数，返回一个指针，指向被替换的 new-handler 函数。

好的 `new-handler` 应该：

- 让更多内存被使用

- 安装另一个 new-handler

- 卸除 new-handler

- 抛出 `bad_alloc`

- 不返回，通常 `abort` 或 `exit`.
