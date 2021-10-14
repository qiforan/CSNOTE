# handy 简洁易用的C++11网络库

## 1. 语法知识

### 可变参数宏

方法一：

`__VA_ARGS__` 宏用来表示可变参数的内容，简单来说就是将左边宏中 `…` 的内容原样抄写在右边 `__VA_ARGS__` 所在的位置。

```cpp
#define debug(...) printf(__VA_ARGS__)
int main()
{
    int year = 2018；
    debug("this year is %d\n", year);  //效果同printf("this year is %d\n", year);
}
```

方法二：

```cpp
#include <stdio.h>
#define debug(format, args...) printf(format, args)
int main(void)
{
    int year = 2018；
    debug("this year is %d\n", year);  //效果同printf("this year is %d\n", year);
}
```

可变参数宏中的可变参数必须至少有一个参数传入，不然会报错，为了解决这个问题，需要一个特殊的 `##` 操作，如果可变参数被忽略或为空，`##` 操作将使预处理器(preprocessor)去除掉它前面的那个逗号。

```cpp
#define debug(format, args...) printf(format, ##args)
```

### 宏中的 `#`

1. 宏连接 `##`，`#define XNAME(n) x##n`可用于生成变量名。

2. 字符串化 `#`, `#define B(x) #x` 将 `x` 变成字符串 `"x"`。

3. 字符化 `#@`, `#define C(x) #@x`, 将 `#` 变成字符 `'x'`。

### 宏语句

宏可以定义函数，也可以定义多条语句。

```cpp
#define foo(x) do { bar(x); baz(x); } while (0) 
```

使用 `do{...}while(0)` 构造后的宏定义不会受到大括号、分号等的影响，总是会按你期望的方式调用运行。


## epoll

由内核维护监视的文件描述符。

```cpp
#include <sys/epoll.h>
int epoll_create(int size);
int epoll_ctl(int epfd,int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

## 编程技巧

### 1. 使用析构函数来调用收尾函数

以文件操作为例，把 `close()` 装入析构函数自动调用。

```cpp
struct ExitCaller : private noncopyable {
    ~ExitCaller() { functor_(); }
    ExitCaller(std::function<void()> &&functor) : functor_(std::move(functor)) {}

   private:
    std::function<void()> functor_;
};

int main()
{
    int fd = open(filename.c_str(),O_RDONLY);
    ExitCaller ec([=] {close(fd);});
}
```

### 2. 桥接模式

桥接模式是一种结构型设计模式，它把类的具体实现细节对用户隐藏起来，以达到类之间的最小耦合关系。桥接模式也被称为 `pimpl惯用法`，它可以将头文件的依赖关系降到最小，减少编译时间，而且可以不适用虚函数实现多态。

