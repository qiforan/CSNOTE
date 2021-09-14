# java

## volatile 特性

内存屏障也称为内存栅栏或栅栏指令，是一种屏障指令，它使 CPU 或编译器对屏障指令之前和之后发出的内存操作执行一个排序约束。 这通常意味着在屏障之前发布的操作被保证在屏障之后发布的操作之前执行。

### 内存屏障

共分为四种类型：

#### LoadLoad 屏障

抽象场景：Load1; LoadLoad; Load2

Load1 和 Load2 代表两条读取指令。在 Load2 要读取的数据被访问前，保证 Load1 要读取的数据被读取完毕。

#### StoreStore 屏障

抽象场景：Store1; StoreStore; Store2

Store1 和 Store2 代表两条写入指令。在 Store2 写入执行前，保证 Store1 的写入操作对其它处理器可见

#### LoadStore 屏障

抽象场景：Load1; LoadStore; Store2

在 Store2 被写入前，保证 Load1 要读取的数据被读取完毕。

#### StoreLoad 屏障

抽象场景：Store1; StoreLoad; Load2

在 Load2 读取操作执行前，保证 Store1 的写入对所有处理器可见。StoreLoad 屏障的开销是四种屏障中最大的。

在一个变量被 volatile 修饰后，JVM 会为我们做两件事：

1. 在每个 volatile 写操作前插入 StoreStore 屏障，在写操作后插入 StoreLoad 屏障。

2. 在每个 volatile 读操作前插入 LoadLoad 屏障，在读操作后插入 LoadStore 屏障。

效果：

* 保证变量在线程之间的可见性。

* 阻止编译时和运行时的指令重排。
