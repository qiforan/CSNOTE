# 进程间通信

* 管道

* XSI IPC

* socket

## 管道

管道可分为命名管道和匿名管道。

管道由内核提供，单工，有自同步机制。

```c
#include <unistd.h>
// pipefd[0] 读端
// pipefd[1] 写端
int pipe(int pipefd[2]);
```

适合于有血缘关系进程之间通信， 常见：建立匿名管道后，fork 得到的子进程复制父进程的文件描述符信息，父子进程通过管道通信。

## XSI IPC

* 消息队列
* 信号量
* 共享内存

### 消息队列

```c
#include <sys/types.h>
#include <sys/ipc.h>
// 获取一个唯一 key 值，由 pathname 和 proj_id 共同决定
key_t ftok(const char *pathname, int proj_id);
#include <sys/msg.h>
// 获得一个消息队列
int msgget(key_t key, int msgflg);
// 发送和接收是双工的
// 发送
int msgsnd(int msgid, const char *msgp, size_t msgsize, int msgflg);
// 接收
int msgrcv(int msgid, void *msgp, size_t msgsize, int msgflg);
// 设置
int msgctl(int msgid, int cmd, struct msgid_ds *buf);
```

## socket


### 常见问题

1. 字节序
2. 对齐
3. 类型长度

#### 字节序

大端：低地址放高字节

小端：低地址放低字节

不同机器的字节序不一致。

解决：转换为主机序和网络序的转换。

#### 对齐

编译器为了减小取指周期，对结构体进行对齐，导致结构体的大小变化，不利于网络传输。

解决：禁止结构体对齐，保持结构体 size 不变。

#### 类型长度

基本变量类型长度不一致。

解决：使用确定长度的变量类型。

### 报式套接字

被动端先运行起来

```c
// 1. 获取 socket，
int sd = socket(AF_INET, SOCK_DGRAM, 0);
// 2. 给 socket 取得地址
struct sockaddr_in laddr;
// 协议族
laddr.sin_family = AF_INET;
// 端口号
laddr.sin_port = htons(atoi(RCVPORT));
inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
// 使用结构体绑定地址
bind(sd, (void* )&laddr, sizeof (laddr));
// 3. 收发消息

// 4. 关闭 socket

```

主动端：

1. 获取 socket
2. 给 socket 取得地址（可省略）
3. 收发消息
4. 关闭 socket


## 问题

1. `0.0.0.0` 与 `127.0.0.1` 的区别
