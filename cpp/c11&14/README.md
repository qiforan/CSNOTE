# C++ 新标准

## variadic templates

## spaces in templates

```cpp
vector<vector<int> > v; // always right
vector<vector<int>> v;  // since c++11
```

## nullptr and std::nullptr_t

C++11 lets you use `nullptr` instead of `0` or `NULL` to specify a pointer refers to no values.

```cpp
void f(int);
void f(void*);
f(0); // call f(int)
f(NULL); // call f(int) if NULL is 0
f(nullptr); // call f(void*);
```

`nullptr` is a new **keyword**, which type is `std::nullptr_t`, defined in `<cstddef>`.

## Automatic Type Deduction with `auto`

```cpp
auto i = 42; // i has type int
double f();
auto d = f(); // d has type double
```

Using auto is especially useful wherer the type is a pretty long and/or complicated expression.

## Uniform Initialization

For any initialization, you can use **one common syntax** using braces.

```cpp
int values[] {1,2,3};
vector<int> v{2,3,4,5};
```

## Initializer Lists

An initializer list forces so-called value initialization, which means that even local variables of fundamental data types are initialized by zero.

However, the narrowing initializations are not possible with braces.

```cpp
int a(5.3);
int a {5.3}; // not allowed, warning
```

C++11 provides the class template `std::initializer_list<>`. It can be used to support initializations by a list of values or in any other place where you want to process just a list of values.

```cpp
void print(std::initializer_list<int> vals){
  for(auto p = val.begin(); p != val.end(); p++){
    ...
  }
}
print({1,2,3});
```

When there are constructors for both a specific number of arguments and a initializer list, the version with the initializer list is perferred.

The initializer_list objects refers to the elements of this array without containing them.

```cpp
cout << max({1,2,3}) << endl;
```

## `explicit` keyword

### `explicit` for ctors taking one argument

```cpp
struct Complex
{
  int real,imag;
  explicit Complex(int re, int im=0): real(re), imag(im):{}
  Complex operator+(const Complex& x){
    return Complex(real+x.real, imag+x.imag);
  }
};
Complex c1(12,5);
Complex c2 = c1 + 5; // Error: not match for operator+
```

### `explicit` for ctors taking more than one argument
