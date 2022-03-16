# C++ templates 笔记

## 1 Function Temlates

### 1.1 函数类型初探

函数模板(Function Template)是参数化的函数，可以代表一类函数。函数模板和普通函数非常相似，除了函数模板的某些类型是没有指定的。

以下是一个返回两个数中最大值的函数模板。

```c++
template<typename T>
T max(T a, T b)
{
    return b < a ? a : b;
}
```

语法上，函数模板总是以 `template< cooma-separated-list-of-parameters >` 开头。

这个函数模板的参数类型是未定的，这意味着可以代表任意类型，只要替换生成的函数是有效的。出于历史原因，上面的 `typename` 关键字可使用 `class` 替换，但不建议使用。

以下展示如何使用函数模板：

```c++
int i = 42;
// :: 表示该函数位于全局命名空间，与 std::max 区分
std::cout << "max(7,i): " << ::max(7,i) << "\n";
double f1 = 3.4;
double f2 = -6.7;
std::cout << " max(f1,f2): " << ::max(f1,f2) << "\n";
std::string s1 = " mathematics" ;
std::string s2 = " math" ;
std::cout << " max(s1,s2): " << ::max(s1,s2) << "\n";
```

函数模板并不会编译生成一个可以处理任何类型的实体，而是根据实际使用情况生成不同类型的实体。所以，上述代码会生成三个不同的函数。例如，对于 `int` 作为模板的参数类型，生成如下的函数：

```cpp
int max(int a, int b)
{
    return b < a ? a : b;
}
```

替换函数模板的参数类型为具体类型的过程被称为实例化(instantiation)，表示产生模板的实例。
上面 `::max()` 函数模板只对部分类型有效，对其他类型可能无效，如 `std::complex<float>`，因为`std::complex<float>` 类型不能比较大小。这类无效的实例会在编译期就会被发现。

### 1.2 模板参数推断

在不引起歧义下，函数模板可以推断出实例化的模板参数。

## Tricky Basics

### `typename` 关键词


`typename` 关键词用来标识模版里的标识符是一个类型，考虑以下代码

```c++
template<typename T>
class MyClass{
public:
    void foo(){
        typename T::SubType* ptr;
    }
};
```

`T` 可能是一个类类型，那么 `T::SubType` 既可能是一个类型，也可能是一个静态变量，那么是一个静态变量。在后面这种情况下，如果没有 `typename`, 这条语句可以表示为一个乘法运算。

### 零初始化

基础类型没有默认构造函数。如果想要给基础类型变量默认零值，就要使用零初始化。

```cpp
template<typename T>
void foo()
{
    T x{};
}
```

如果 `T` 是类类型，则调用默认构造函数，如果是基础类型，则赋予零值。

> 零值对于 `bool` 类型来说是 `false`; 对于指针类型来说是 `nullptr`.

### Using `this->`

如果父类是模板类，直接调用父类成员的话，会找不到该变量。

```cpp
template<typename T>
   class Base {
     public:
       void bar();
};
template<typename T>
class Derived : Base<T> {
    public:
    void foo() {
        bar(); // calls external bar() or error 
    }
}
```

可以使用 `this->` 或者 `Base<T>::`。

### 原生数组和字符串

如果给函数参数传数组引用，就不会有指针退化。

```c++
template<typename T, int N, int M>
bool less(T (&a)[N], T (&b)[M])
{
    for(int i = 0; i < N && i < M; i++){
        if(a[i] < b[i]) return true;
        if(a[i] > b[i]) return false;
    }
}
```

## 6 Move Semantics and `enable_if<>`

### 6.1 Perfect Forwarding

### 6.3 Disable Templates with `enable_if`

```cpp
// Possible implementation
template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };
```

`std::enable_if` 在编译时评估尖括号里给定的(第一个)表达式：

* 如果为真，则成员类型 `type` 为 `void` 或为尖括号里第二个表达式；
* 如果为假，则类型未定义。

## 8 编译时编程

C++11 中的 `constexpr` 指定的函数返回值和参数必须要保证是字面值，而且必须有且只有一行 `return` 代码，这给函数的设计者带来了更多的限制，比如通常只能通过 `return` 三目运算符+递归来计算返回的字面值。
C++14 中只要保证返回值和参数是字面值就行了，函数体中可以加入更多的语句，方便了更灵活的计算。