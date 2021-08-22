# 高级 I/O

系统调用可以分为两类：“低速”系统调用和其他。前者可能会使进程永远阻塞，包括：

- 某些文件类型的数据不存在，读操作不能完成。

- 数据不能被接受，写操作不能完成。

- 打开文件之前的某些操作不能完成，导致打开文件操作不能完成。

- 读加锁的文件读写。

- 某些 ioctl 操作。

- 某些进程通信函数。

非阻塞 I/O 操作使我们不被不能完成的操作阻塞，而是出错返回。

对于一个操作符，设置 `O_NONBLOCK` 标志可以指定为非阻塞，具体地：

- 在调用 `open` 时，给 `oflag` 参数指定 `O_NONBLOCK` 标志

- 若已经打开，调用 `fcntl` 设置 `O_NONBLOCK` 标志

## 多路转接

### select

为每个条件(可读、可写和异常条件) 构造描述符集合。

```c
#include <sys/select.h>
int select(int nfds,               // 最大文件描述符加 1
           fd_set *readfds,        // 监视 读的描述符集合，下面两个类似
           fd_set *writefds,
           fd_set *exceptfds,
           struct timeval *timeout // 超时时间
          )
```

`fd_set` 数据类型由实现决定，使用对应接口进行操作，接口可实现为宏或函数。

申明一个描述符集(fd_set) 后，必须先 `FD_ZERO` 置 0，然后设置描述符的位。

```c
void FD_CLR(fd, fd_set *fdset);

int FD_ISSET(fd, fd_set *fdset);

void FD_SET(fd, fd_set *fdset);

void FD_ZERO(fd_set *fdset);
```

当 `select` 返回时：

* 返回 -1， 表示出错

* 返回 0, 没有描述符准备好

* 已经准备好的描述符，同一个描述符可重复计数。具体结果存放于 3 个 描述符集

`select` 的问题：

* 需要把 `fd_set` 在用户空间与内核空间之间进行拷贝，效率低

* 支持的文件描述符数量限制，默认只有 1024

### poll

通过构造一个 `pollfd` 结构数组，每个数组指定描述符编号和我们对其感兴趣的条件。

```c
#include <poll.h>
struct pollfd
{
    int fd;
    short events;             // 设置要观察的事件 
    short revents;            // 内核设置哪些事件发生
};
int poll(struct pollfd fds[], // 结构体数组
         nfds_t nfds,         // 数组个数
         int timeout          // 超时时间(毫秒)
        )
```

### epoll

方言，在 Linux2.6 内核中正式引入。

`epoll` 通过监控注册多个描述字进行 IO 事件的分发，不仅提供默认的 level-trigger 机制还提供了边缘触发机制。

```c
// 1. 创建一个 epoll
// size 告诉内核期望监控多少个描述符，现在不需要这个参数
int epoll_create(int size);

// 2. 布置监控任务
int epoll_ctl(int epfd,                 // epoll 描述符，由上个函数返回
              int op,                   // 控制操作，包括 添加、删除、修改
              int fd,                   // 感兴趣的描述符
              struct epoll_event *event // 注册的事件类型
             );

// 3. 获取结果
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

epoll = 一颗红黑树 + 一张准备就绪句柄链表 + 少量的内核 cache

## 存储映射

将磁盘文件映射到存储空间的一个缓冲区上。读写缓冲区就相当于读写文件。

```c
#include <mman.h>
// 成功 返回映射起始地址
void *mmap(void *addr,        // 映射区起始地址，0表示由系统选择
           size_t len,        // 要映射的字节数
           int prot,          // 映射区保护要求
           int flag,          // 属性设置
           int fd,            // 映射文件的描述符
           off_t off);        // 文件的偏移量
           
// 解除映射
int munmap(void *addr,        // 映射起始地址
           size_t length);    // 映射长度
```

匿名映射可以实现 `malloc/free`.


