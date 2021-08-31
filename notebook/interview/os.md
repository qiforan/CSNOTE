# 进程

### 1. 进程调度的方式有哪些？Linux中进程调度的方式？

* 先来先服务调度算法
* 短作业 (进程) 优先调度算法
* 优先权调度算法
* 高响应比优先调度算法
* 时间片轮转法

Linux 基于 **时间片调度**，实时进程优先于普通进程，实时进程以进程的紧急程度为优先顺序，并为实时进程赋予固定的优先级；普通进程则以保证所有进程能平均占用处理器时间为原则。

Linux 进程调度的 **时机** 主要有：

* 进程状态转换的时刻，如进程中止、进程睡眠等；
* 可运行队列中新增加一个进程时；
* 当前进程的时间片用完时；
* 进程从系统调用返回用户态时；
* 内核处理完中断后，进程返回用户态时。

[Linux 的进程调度](https://blog.csdn.net/qq_38410730/article/details/81253686)

[Linux 进程调度原理](https://www.cnblogs.com/zhaoyl/archive/2012/09/04/2671156.html)

### 2. 多线程与多进程

内核提供了两个系统调用 `__clone()` 和 `fork()`，最终都用不同的参数调用 `do_fork()` 核内 API。 `do_fork()` 提供了很多参数，包括 CLONE_VM（共享内存空间）、CLONE_FS（共享文件系统信息）、CLONE_FILES（共享文件描述符表）、CLONE_SIGHAND（共享信号句柄表）和 CLONE_PID（共享进程 ID，仅对核内进程，即 0 号进程有效）。

* 当使用 `fork()` 系统调用产生多进程时，内核调用 `do_fork()`  不使用任何共享属性，进程拥有独立的运行环境。
* 当使用 `pthread_create()` 来创建线程时，则最终设置了所有这些属性来调用 `__clone()`，而这些参数又全部传给核内的 `do_fork()`，从而创建的 “进程” 拥有共享的运行环境，只有栈是独立的，由 `__clone()` 传入。

即： Linux 下不管是多线程编程还是多进程编程，最终都是用 do_fork 实现的多进程编程

### IO 复用

I/O 复用原理：让应用程序可以同时对多个 I/O 端口进行监控以判断其上的操作是否可以进行，达到时间复用的目的。

select 的问题:

* select 会修改传入的参数数组
* select 仅仅会返回，但是并不会告诉你是那个 sock 上有数据，需要自己找
* select 只能监视 1024 个链接，linux 定义在头文件中的，参见 FD_SETSIZE
* select 不是线程安全的

epoll 现在是线程安全的

[IO复用、多进程和多线程三种并发编程模型](https://blog.csdn.net/wan_hust/article/details/38441455)

[如果这篇文章说不清epoll的本质，那就过来掐死我吧！](https://zhuanlan.zhihu.com/p/63179839)

### 4. 僵尸进程和孤儿进程？

孤儿进程：父进程退出，子进程将成为孤儿进程，`init` 进程 (进程号为 1) 所收养，并由 `init` 进程对它们完成状态收集工作。

僵尸进程：子进程运行结束，父进程却没有使用 `wait() / waitpid()` 来清理子进程的进程信息，仍在内核的进程表中占据一条记录。

### 5. 进程能不能绑定到 cpu

第一种：shell 命令 taskset

第二种`pthread_setaffinity_np` 和 `sched_setaffinity` 函数接口。

[如何将一个进程（线程）绑定到一个固定的CPU核上？](https://blog.csdn.net/sangyongjia/article/details/50725734)

[Linux进程或线程绑定到CPU](https://www.cnblogs.com/swey/p/4469722.html)

[管理处理器的亲和性（affinity）](https://www.ibm.com/developerworks/cn/linux/l-affinity.html)

[一个进程能不能在多个核上跑？](https://www.zhihu.com/question/31683094?sort=created)

### 8. 进程通信的机制有哪些？（IPC）

* 管道（命名管道FIFO，无名管道PIPE）

* 共享内存
* 信号量
* 消息队列

* socket

### 9. 可重入函数

重入即表示重复进入，首先它意味着这个函数 **可以被中断**，其次意味着它除了使用自己栈上的变量以外不依赖于任何环境。

编写可重入函数规则：

1. 不要使用全局变量。因为别的代码很可能改变这些变量值。
2. 在和硬件发生交互的时候，切记执行类似 `disinterrupt()` 之类的操作，就是关闭硬件中断。完成交互记得打开中断，在有些系列上，这叫做 “进入 / 退出核心”。
3. 不能调用其它任何不可重入的函数。
4. 谨慎使用堆栈。

### 10. 父进程子进程共享什么？

[父子进程共享内容](https://blog.csdn.net/zhuoyue01/article/details/105976937/)

### 15. 饿汉模式；懒汉模式；线程安全的写法

1. 饿汉模式：在类被加载的时候创建实例（线程安全的）

2. 懒汉模式：在方法被运行的时候创建实例（线程不安全的） 解决方法：通过双检验

### 16. 一个进程可以打开的fd有限，到并发量很大的时候，fd耗尽了，怎么办？

修改 `/etc/security/limits.conf` 文件

[为什么select打开的FD数量有限制，而poll、epoll等打开的FD数量没有限制？](https://www.zhihu.com/question/37219281?sort=created)

### 17. 惊群模式

[Linux惊群效应详解（最详细的了吧）](https://blog.csdn.net/lyztyycode/article/details/78648798?utm_source=blogxgwz2)

[Linux网络编程“惊群”问题总结](https://www.cnblogs.com/Anker/p/7071849.html)

[Linux网络编程“惊群”问题](https://www.jianshu.com/p/9d0899c9ec89)

[什么是惊群，如何有效避免惊群?](https://blog.csdn.net/thlzjfefe/article/details/97495073)

[解决多进程模式下引起的“惊群”效应](https://zhuanlan.zhihu.com/p/42882130)

[框架高并发中的惊群效应](https://blog.csdn.net/second60/article/details/81252106)

### 18. 进程切换上下文细节

[进程切换（进程上下文和中断上下文）详解](https://blog.csdn.net/yapian8/article/details/41809837)

[进程上下文切换分析](https://www.cnblogs.com/tjyuanxi/p/9314810.html)

[进程/线程上下文切换会用掉你多少CPU？](https://www.jianshu.com/p/ebf1f832694c)

### 19. 不同进程是如何保证使用的内存互不影响

**内存保护**实现互不干扰，如页式管理中有页地址越界保护，段式管理中有段地址越界保护。

### 20. 进程挂了共享内存是否还存在，为什么？

[Linux进程间通信之共享内存](https://www.cnblogs.com/xcywt/p/5128430.html)

[进程间通信——IPC之共享内存](https://www.cnblogs.com/tp-16b/p/8987697.html)

[多进程与多线程的优劣 与 共享内存的同步问题](http://blog.chinaunix.net/uid-27164517-id-3319185.html)

### 21. 父进程如何fork一个子进程的，具体过程,父进程如何fork一个子进程，父进程内部的代码段、数据需要在拷贝一份给子进程吗？如果不拷贝的话，共用的话，内核如何保证他们不会出问题？

写时拷贝。

[fork创建进程过程（底层实现） 和 写时拷贝](https://blog.csdn.net/qq_37924084/article/details/78299352)

### 22. 系统调用的最小单元是什么？线程相对于进程，独占了什么？

[深入理解进程和线程](https://www.cnblogs.com/tiankong101/p/4229584.html)

[【面试高频问题】线程、进程、协程](https://zhuanlan.zhihu.com/p/70256971)

[内核线程、轻量级进程、用户线程三种线程概念解惑（线程≠轻量级进程）](https://blog.csdn.net/gatieme/article/details/51481863)

[进程、线程及进程调度算法](https://www.jianshu.com/p/84957c2644d8)、

## 线程

### 1. 线程池如何开启一个新线程？

### 2. 线程池

[线程池的C++实现](https://zhuanlan.zhihu.com/p/61464921)

[C++11实现线程池](https://blog.csdn.net/u012234115/article/details/89856320)

[【C/C++】 Pthread线程池](https://zhuanlan.zhihu.com/p/88896082)

[用 C++ 写线程池是怎样一种体验？](https://www.zhihu.com/question/27908489/answer/355105668)

### 3. 线程池初始化的步骤？

### 4. 线程池中线程状态？

### 5. 主线程与IO线程之间描述符传递？

[Linux 文件描述符详解](https://www.cnblogs.com/alan666/p/8311890.html)

[Linux文件描述符到底是什么？](http://c.biancheng.net/view/3066.html)

[Linux文件描述符--就这？](https://zhuanlan.zhihu.com/p/134036259)

[linux中的文件描述符(file descriptor)和文件](https://www.jianshu.com/p/504a53c30c17)

### 6. `pthread_detach`和`pthread_join`的作用？

[pthread_join和pthread_detach的作用](https://blog.csdn.net/sinat_29844779/article/details/72490111)

[pthread_join和pthread_detach的用法](https://www.cnblogs.com/fnlingnzb-learner/p/6959285.html)

### 7. 进程线程区别、进程/线程通信

### 8. 锁相关了解吗？线程安全怎么办？（回答可重入函数，锁）

### 9. 线程、进程和协程

[什么是协程 ？](https://juejin.im/post/5d5df6b35188252ae10bdf42)

[协程](https://zh.wikipedia.org/wiki/%E5%8D%8F%E7%A8%8B)

[coroutine协程详解](https://www.jianshu.com/p/2782f8c49b2a)

[协程的好处有哪些？](https://www.zhihu.com/question/20511233)

[协程简介](https://hanfeng.ink/post/coroutine/)

### 10. 死锁的产生条件，怎样预防死锁

[死锁的四个必要条件？如何避免与预防死锁？](https://www.cnblogs.com/bopo/p/9228834.html)

### 11. 一个进程里面有很多线程，设计一个机制，可以知道哪些线程在工作，哪些出了问题

### 12. 为什么用多线程，apache为什么用多进程，nginx为什么用多线程

### 13. 介绍一下几种锁（互斥、信号量、条件变量、读写锁、自旋锁）

### 14. 运用多线程有什么要注意的吗？（join回收子线程）还有啥？

### 15. 子线程正常死亡与其他线程cancel这个子线程（被动死亡）有什么区别？（不知道）

[linux下pthread_cancel无法取消线程的原因](https://blog.csdn.net/qingzhuyuxian/article/details/81019173)

[线程pthread_cancel()函数](https://blog.csdn.net/u011878172/article/details/79510824)

[线程取消(pthread_cancel)](https://www.cnblogs.com/lijunamneg/archive/2013/01/25/2877211.html)

[5、线程终止方式：pthread_cleanup_push/pthread_cleanup_pop()](https://www.cnblogs.com/mydomain/archive/2011/08/15/2139826.html)

### 16. 线程切换上下文细节

### 17. 线程共享一块内存，进程不共享，线程全都共享吗

[linux线程共享和进程内存的关系](https://blog.csdn.net/yuanbinquan/article/details/41699491)、[同一进程中的线程究竟共享哪些资源](https://www.cnblogs.com/baoendemao/p/3804677.html)

### 18. 对比I/O多路复用和多线程

## 文件系统

### 2. 五种IO模型？

[五种IO模型（详解+形象例子说明）](https://blog.csdn.net/ZWE7616175/article/details/80591587)
[IO概念和五种IO模型](https://www.cnblogs.com/shengguorui/p/11949282.html)
[五种IO模型透彻分析](https://www.cnblogs.com/f-ck-need-u/p/7624733.html)

### 3. select和epoll有什么区别？epoll的LT和ET模式？LT和ET适用场景？

[select、poll、epoll的区别以及epoll的两种模式（LT、ET）以及实现](https://blog.csdn.net/qq_41038824/article/details/88537640)

[epoll两种类型ET和LT区别(结合实际例子)](https://blog.csdn.net/cws1214/article/details/47662705)

[I/O多路复用之select、epoll的实现和区别 ，ET与LT模式](https://blog.csdn.net/qingcunsuiyue/article/details/66477777)

### 4. select/poll/epoll、虚拟内存、用户态内核态；

### 5. Linux中，文件名存在哪里？

[Linux 中文件名存在哪里？](https://blog.csdn.net/wdkirchhoff/article/details/44205143)

[Linux文件名存在哪儿](https://blog.csdn.net/pugongying_95/article/details/97295843)

### 6. 文件索引有哪些？

### 7. select和epoll有没有最大描述符限制，epoll的限制体现在哪？epoll底层用了哪些数据结构，红黑树和链表分别是用来干啥的，红黑树的key是什么？

[epoll“传说中”的性能](https://blog.csdn.net/historyasamirror/article/details/5833259)

[Linux下实现epoll服务器和缺点总结](https://blog.csdn.net/lishitao_578/article/details/73810623)、

### 8. 从磁盘读取数据到CPU中间经过的介质

硬盘数据--->硬盘缓存---->内存---->CPU缓存--->CPU寄存器与运算器

### 10. IOCP

11. linux系统怎么区别文件类型

[linux操作系统文件类型有哪几种,有什么区别?](https://zhidao.baidu.com/question/511065836.html)、[Linux系统目录结构及文件类型区分](https://www.cnblogs.com/miaotianjie/p/8587650.html)、

### 12. 五种io模型

同步IO：阻塞IO、非阻塞IO、IO多路复用、信号驱动IO；

异步IO

### 13. 什么情况下epoll效率会比select\poll低,epoll底层的实现原理，如何保证大部分情况下效率优于select

### 14. 操作系统读写操作，写文件，read的三种模式，写成功是怎样的，什么情况下写操作会失败

### 15. [Open/Read/Write和Fopen/Fread/Fwrite的区别](https://www.cnblogs.com/ldp-web/archive/2011/10/21/2220180.html)、[多进程同时写一个文件会怎样？（待修订）](https://blog.csdn.net/yangbodong22011/article/details/63064166/)

## 中断

1. 中断的上半部与下半部的区别，什么是中断时延