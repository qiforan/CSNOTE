# 线程 Thread

POSIX 线程是一套标准，而非实现。例如，`pthread_t` 具体类型取决于不同系统的实现。

## 基本概念

UNIX 进程可以看成线程容器。

多线程的好处：

* 简化异步事件的代码。
* 相比多进程，能访问相同的存储地址空间和描述符。
* 分解问题，以提高整个程序的吞吐量。
* 改善交互程序的响应时间。

每个线程都有

* 线程 ID

* 一组寄存器值、栈

* 调度优先级和策略

* 信号屏蔽字

* errno 变量以及线程私有数据

线程 ID 是用 pthread_t 表示，Linux 下为 **整型数**。

```c
// 比较两个线程 ID
int pthread_equal(pthread_t p1, pthread_t p2); 
// 获取当前线程 ID
int pthread_self(void); 
```

使用 POSIX 线程需引入 `pthread.h` 头文件。

```makefile
CFLAGS+=-pthread
LDFLAGS+=-pthread
```

>-pthread Adds support for multithreading with the pthreads library. This option sets flags for both the preprocessor and linker.

## 线程创建

```c
// 成功返回 0， 失败返回 错误号
int pthread_create(pthread_t *thread,               // 传一个线程 ID，让函数回填
                   const pthread_attr_t *attr,      //线程属性，大部分情况默认 NULL
                   void *(*start_routine)(void *),  // 函数地址
                   void *restrict arg);             // 传递给函数的参数
```

线程的调度策略取决于调度器策略

## 线程的终止

任一进程调用了 `exit`、`_Exit` 和 `_exit`，那么整个进程终止。

在不终止整个进程的情况下，线程的结束方式：

1. 非主控线程从启动例程返回(函数执行完成)，返回值是退出码
2. 被同一进程的其他线程取消(pthread_cancel)
3. 线程主动调用 pthread_exit

```c
pthread_exit(void *rval_ptr);
// 相当于 进程的 wait 函数
pthread_join(pthread_t thread, void **rval_ptr);
```

### 栈的清理

类似于 `atexit` ，线程清理处理函数可以在线程结束时做一些清理工作，其实现为宏。

```c
// pthread_cleanup_push 要与 pthread_cleanup_pop 数量和顺序匹配，否则报错。
pthread_cleanup_push(void (*routine)(void *), void *arg);
pthread_cleanup_pop(int execute);
```

### 线程取消

给线程发送一个取消请求。

```c
int pthread_cancel(pthread_t tid);
```

仅仅是提出请求，线程可以选择忽略取消或者选择何时取消。

取消选项分为 可取消状态 和 可取消类型，前者表示是否可以被取消，默认为是。
尽管设置为不可取消，取消请求也不是消失而是挂起，等待设置为可取消再响应。
当然也可以自定义取消点，或者选择即时取消而不是延迟取消。

允许取消（默认）不是即时取消，而是推迟到 **取消点** 再取消。
>POSIX 定义的取消点，都是可能引发阻塞的系统调用。

```c
// 设置可取消状态
// 并把原来的状态存储于 oldstate
// 该操作为原子操作
int pthread_setcancelstate(int state, int *oldstate);

// 当有取消请求时，主动取消
// 本函数啥也不做，仅设置取消点
void pthread_testcancel(void);

// 设置取消类型，可用选项为延迟取消和异步取消，后者即时取消，不用等待到取消点
int pthread_setcanceltype(int type,int *oldstate);
```

### 线程分离

分离一个线程
> 线程是可结合（joinable）或者是可分离的（detached）。
> 一个可结合线程是可以被其他线程收回资源和杀死的。在被回收之前，他的存储器资源（栈等）是不释放的。
> 而对于 detached 状态的线程，其资源不能被别的线程收回和杀死，只有等到线程结束才能由系统自动释放

```c
int pthread_detach(pthread_t thread);
```

## 线程同步

### 互斥量

互斥量 pthread_mutex_t 使用前必须初始化。可以静态初始化或动态初始化。

动态初始化的互斥量，在释放内存前，调用 pthread_mutex_destroy.

```c
// 静态初始化，无需销毁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 动态初始化
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
// 销毁，与动态初始化配合
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

临界区使用互斥锁

```c
// 获取锁，阻塞
int pthread_mutex_lock(pthread_mutex_t *mutex);
// 获取锁，不阻塞
int pthread_mutex_trylock(pthread_mutex_t *mutex);
// 解锁
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

### 条件变量

条件变量 `pthread_cond_t` 需要与互斥锁配合。类似互斥锁，条件变量初始化也有两种方式。

```c
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);
// 唤醒所有
int pthread_cond_broadcast(pthread_cond_t *cond);
// 唤醒任意一个（不确定）
int pthread_cond_signal(pthread_cond_t *cond);
// （解锁）等待唤醒
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
```

### 信号量

信号量和互斥锁 (mutex) 的区别：互斥锁只允许一个线程进入临界区，而信号量允许多个线程同时进入临界区。

## 属性设置

### 线程属性

属性值不能直接设置，须使用相关函数进行操作。

```c
// 线程属性结构
typedef struct  
{  
    int                   etachstate;      // 线程的分离状态  
    int                   schedpolicy;     // 线程调度策略  
    structsched_param     schedparam;      // 线程的调度参数  
    int                   inheritsched;    // 线程的继承性  
    int                   scope;           // 线程的作用域  
    size_t                guardsize;       // 线程栈末尾的警戒缓冲区大小  
    int                   stackaddr_set;   // 线程的栈设置  
    void*                 stackaddr;       // 线程栈的位置  
    size_t                stacksize;       // 线程栈的大小  
}pthread_attr_t;
```

### 互斥量和条件变量属性

类似线程属性，互斥量和条件变量也可以设置属性。

## 重入

函数如果能相同的时间点被多个线程安全调用，则是 **线程安全**。

标准 I/O 是线程安全的。

## 其他标准

[openmp](www.openmp.org)

