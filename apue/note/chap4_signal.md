# 信号（Signal）

## 概述

信号是软件中断，信号提供了一种处理异步事件的方法。终端键入中断键，通过信号机制终止一个程序。 信号是异步事件的经典实例。 每个信号都有一个名字，以 SIG 开头，在 <signal.h> 中，信号被定义为正整数常量（信号编号）。

信号处理有三种方式：

1. 忽略。大部分信号都可以忽略，除了 SIGKILL 和 SIGSTOP。
2. 捕捉。自定义程序处理出现的信号。
3. 默认。执行默认动作，对于大部分信号，默认是终止程序。

## 函数 signal

函数 signal 为信号定义一个动作。

```c
#include
<signal.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```

注意：

1. 第二个参数可以是 SIG_IGN（忽略），SIG_DFL（默认）或是调用函数的地址。
2. 信号会打断阻塞的系统调用。

## 不可靠的信号

不可靠是指，信号可能丢失，且进程不能主动阻塞信号。

早期有一个问题，进程正在进行信号动作时，会忽略此时到来的信号（即执行默认动作）。

## 可重入函数

所有的系统调用都是可重入的，部分库函数也是可重入的，如：memcpy。

库函数不可重入大部分是因为：

1. 使用静态数据结构
2. 调用 malloc 或 free
3. 标准 I/O

## 信号的响应过程

信号产生，实质是内核在进程表中以某种形式设置一个标志位。信号递送，就是指进程对信号采取动作，在产生和递送之间，有时间间隔，我们称信号是未决的。

每个进程都有一个信号屏蔽器（signal mask)。简单讲，信号屏蔽器是一个位图，其中每一位对应一种信号，可以设置位图来屏蔽信号与取消屏蔽信号。 每次检查到来的信号和 signal mask 来决定是否响应信号。

## 函数 kill

kill 将信号发给进程或进程组。

```c
#include
<signal.h>
int kill(pid_t pid, int signo);
int raise(int signo);
```

kill 的 pid 参数情况：

1. pid > 0，指定pid进程
2. pid == 0, 同属进程组进程
3. pid == -1，有权限发送的进程
4. pid < -1，指定进程组内的进程（1 进程除外）

已知没有为 0 的 signo，如果 signo 为 0，不发送信号，而是检查特定进程是否存在。

## 函数 raise

给当前进程发送信号。

## 函数 alarm 和 pause

函数 alarm 可以设置一个定时器，定时产生 SIGALRM，默认终止程序。

```c
unsigned int alarm(unsigned int seconds);
```

## 函数 abort

```c
#include
<stdlib.h>
void abort();
```

给当前进程 SIGABRT 信号，结束当前进程并产生 coredump 文件。

## 函数 system

执行期间会 block SIGCHLD 信号，ignore SIGINT 和 SIGQUIT 信号。

## 函数 sleep

不建议使用 sleep 函数，因为有些平台使用 alarm 和 pause 实现 sleep，如果程序已经使用了 alarm 函数，则会干扰。

当前平台使用 nanosleep 实现，没有这个问题。

## 信号集

```c
#include
<signal.h>

int sigemptyset(sigset_t *set); // 清空一个信号集
int sigfillset(sigset_t *set); // 全选所有信号
int sigaddset(sigset_t *set, int signum); //添加一个信号
int sigdelset(sigset_t *set, int signum); // 移除一个信号
int sigismember(const sigset_t *set, int signum); // 判断信号是否存在于信号集
```

## 信号屏蔽字/pending 集

```c
#include <signal.h>

/* Prototype for the glibc wrapper function */
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
/* Prototype for the underlying system call */
int rt_sigprocmask(int how, const kernel_sigset_t *set, kernel_sigset_t *oldset, size_t sigsetsize);
/* Prototype for the legacy system call (deprecated) */
int sigprocmask(int how, const old_kernel_sigset_t *set, old_kernel_sigset_t *oldset);
int sigpending(sigset_t *set)
```

## 函数 sigaction

```c
#include <signal.h>
int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);
```

## 实时信号

实时信号不丢失，会排队


