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
