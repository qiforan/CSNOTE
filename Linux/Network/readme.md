# Linux 网络编程

## Socket 编程

socket 可以看成用户进程与内核网络协议栈的编程接口。

### 套接字地址

套接字地址结构定义在 `netinet/in.h` 中。

```c
struct sockaddr_in {
// 结构体长度
  uint_8 sin_len;
// 地址家族，对于 IPV4 来说，该值为 AF_INET
  sa_family_t sin_family;
// 端口，16位无符号整数，最大为 65535
  in_port_t sin_port;
// IPV4 地址，仅有一个无符号的32位整数成员
  struct in_addr sin_addr;
// 保留字段
  char sin_zero[8];
};
```

结构体中字段应该为 **网络字节序** 。

通用地址结构用来指定与套接字关联的地址

```c
struct sockaddr {
// 结构体长度
  uint8_t sin_len;
// 地址家族
  sa_family_t sin_family;
// 具体地址，由上个字段决定形式
  char sa_data[14];
}
```

实际编程中，会将套接字地址结构强制转换为通用地址结构。

### 字节序

**大端字节序** , 最高有效位存储于最低内存地址处。
**小端字节序** ，最高有效位存储于最高地址内存处。

不同主机的字节序可能不一致，如 x86 是小端字节序，Motorola 6800 是大端字节序，ARM 的字节序是可配置的。

**网络字节序** 规定为大端字节序。

字节序转换函数：

```c
#include <netinet/in.h>
#include <arpa/inet.h>
// 同下，输出在指针指向的地址
int inet_aton(const char *cp, struct in_addr *inp);
// 将点分十进制的字符串转换为网络字节序的32位整数
in_addr_t inet_addr(const char *cp);
// 将网络字节序的32位整数转换为点分十进制的ip地址字符串
char *inet_ntoa(struct in_addr in);
```

### 套接字类型

**流式套接字**, 对应于 TCP 协议。提供面向连接、可靠、双向、面向字节流的数据传输。

**数据报套接字**, 对应于 UDP 协议。提供无连接服务。不提供无错保证，数据可能丢失或重复且接收顺序混乱。

**原始套接字**.

## C/S 模型

**主动套接字** 会调用 `connect()` 发起连接, **被动套接字** 会调用 `accept()` 接受连接。

对于给定的套接字接口，内核要维护两个队列：
1. 已由客户端发出并达到服务器，正在进行三次握手 (SYN_RCVD)
2. 已完成连接的队列 (ESTABLISHED)

两个队列之和不超过 `backlog`

`accept`  从已完成连接队列中返回第一个连接，如果已连接队列为空，则阻塞。

```c
```

