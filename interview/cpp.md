# 面试

## C 语言

### 可变参数

[C语言中的可变参数（printf的实现原理）](https://blog.csdn.net/yzy1103203312/article/details/80808741)

[C语言实现printf函数，即参数可变函数原理](https://blog.csdn.net/gengyiping18/article/details/50603326)

### ++i， i++是否是原子操作

[i++和++i是否为原子操作](https://blog.csdn.net/u010214092/article/details/50634430)

[i++是否原子操作](https://www.cnblogs.com/lxd2502/p/4648020.html)

### c语言的函数调用栈底层详细说说？  

[C语言函数调用栈(一)](https://www.cnblogs.com/clover-toeic/p/3755401.html)

[C语言函数调用栈(二)](https://www.cnblogs.com/clover-toeic/p/3756668.html)

[c语言函数调用过程中栈的工作原理理解](https://blog.csdn.net/qq_31567335/article/details/84782202)

[C语言函数调用的底层机制](https://blog.csdn.net/maochengtao/article/details/61630370)

### static变量存放在哪里？什么时候分配的内存？

静态变量属于静态存储方式，其存储空间为内存中的静态数据区.

### 数据类型及大小

short类型占几个字节，int 类型占几个字节，short和int相加时会有隐式类型转换，对于补码来说，这个转换是在short的高字节位填充什么？把一个负数转换为补码形式最简单的方法应该是怎么做？

在32位环境中，char 8位，short 16位，int 32位，long 32位，int*（泛指指针）32位，long long 32位，float 32位，double 64位

在64位环境中，char 8位，short 16位，int 32位，long 64位，int*（泛指指针）64位，long long 32位，float 32位，double 64位

在类中，如果什么都没有，则类占用1个字节，一旦类中有其他的占用空间成员，则这1个字节就不在计算之内，如一个类只有一个int则占用4字节而不是5字节。

如果只有成员函数，则还是只占用1个字节，因为类函数不占用空间

虚函数因为存在一个虚函数表，需要4个字节，数据成员对象如果为指针则为4字节，注意有字节对齐，如果为13字节，则进位到16字节空间。

### 带参数的宏

参数表中的参数之间用逗号分隔，字符序列中应包含参数表中的参数。在定义带参数的宏时，宏名标识符与左圆括号之间不允许有空白符

使用 #把宏参数变为一个字符串，用 ## 把两个宏参数贴合在一起

### switch的case里为何不能定义变量

[switch-case内不能定义变量？](https://www.cnblogs.com/Younger-Zhang/p/11316290.html)
[switch - case 中不能定义变量 的解决办法](https://blog.csdn.net/qq_35865125/article/details/104739997)
[请教switch内部的变量定义问题？](https://www.zhihu.com/question/23051685)

### 系统调用和普通函数调用

切换用户栈，内核栈，保存寄存器信息，这些只是基本开销。还有页表切换，不同用户的页表是不一样的，系统调用为了服务不同用户，需要切换页表。切换页表意味着cpu缓存失效。而且内核空间跟用户空间地址空间相差很大，指令预测系统也会失效。系统调用需要在用户空间和内核空间进行切换，普通函数调用只是同一个空间调用，只是压栈这一点开销，相对于系统调用这点开销并不算什么，甚至函数式编程的压栈开销都没有。

[https://www.zhihu.com/question/400440365](https://www.zhihu.com/question/400440365)

## C++ 语法

### c++ 编译和 c 编译

[C/C++：函数的编译方式与调用约定以及extern “C”的使用](https://www.cnblogs.com/qinfengxiaoyue/archive/2013/02/04/2891908.html)

### C++面向对象的三种特性？

封装、继承、多态。

### 重载、重写、覆盖？

重载：函数同名不同参

重写：派生类的函数屏蔽了与其同名的基类函数

覆盖：派生类函数覆盖基类函数

### 继承和组合

类继承通常为 “白箱复用”，对象组合通常为 “黑箱复用”。

继承在某种程度上破坏了封装性，子类父类耦合度高；而对象组合则只要求被组合的对象具有良好定义的接口，耦合度低。

### static关键字

* 在函数体外（全局作用域），限制函数或者对象的使用范围为本文件；
* 在函数体内的静态变量，声明周期为整程序运行周期；
* 类的静态方法与静态成员

### volatile 关键字

保证数据只在内存中读写

[C/C++ Volatile关键词深度剖析](https://www.cnblogs.com/god-of-death/p/7852394.html)

[C++中volatile的作用](https://blog.csdn.net/weixin_41656968/article/details/80958973)

### 那如何实现对一个常量进行引用

### 隐式类型转换

[彻底理解c++的隐式类型转换](https://www.cnblogs.com/apocelipes/p/14415033.html)

### C++ 异常处理

[C++异常处理（try catch throw）完全攻略](http://c.biancheng.net/view/422.html)
[C++异常机制的实现方式和开销分析](http://www.baiy.cn/doc/cpp/inside_exception.htm)
[异常](http://www.baiy.cn/doc/cpp/index.htm#%E4%BB%A3%E7%A0%81%E9%A3%8E%E6%A0%BC%E4%B8%8E%E7%89%88%E5%BC%8F_%E5%BC%82%E5%B8%B8)
[C++异常处理机制](https://blog.csdn.net/caihaitao2000/article/details/79827857)

### inline和宏定义的区别？inline是如何实现的？宏定义是如何实现的？

[C++ inline和#define宏的区别](https://www.cnblogs.com/yanwei-wang/p/8073111.html)

### 指针和引用的区别？怎么实现的？

指针时一个变量，可以用来存储变量的地址，引用只是一个变量的别名，必须依附其他变量存在，内部实现是只读指针。

sizeof(引用) 返回的是变量的大小

[引用和指针的区别](https://www.zhihu.com/question/37608201)

### 虚函数表指针通常存储在类对象的哪个位置?为什么

TODO

### 构造函数可以是虚函数吗

构造函数不能是虚函数。

从 C++ 的视角来看，我们只能在编译时明确我们要构造的类的类型，才可以拿到这个类的构造函数，再使用这个构造函数构造我们想要的类，虚的构造函数从这个角度来看就是一个悖论。

### 析构函数可以是虚函数吗

析构函数可以且常常是虚函数。如果不是虚函数，则使用时可能存在内存泄漏的问题。

情形：用基类指针调用析构函数，使派生类的内存泄露。

### 如果可以确定一个类没有子类，这个类的析构函数还有必要是虚函数吗

没有必要，因为一旦设置成虚函数，则对象中一定会有虚函数表占用额外的存储空间，况且虚函数的调用需要从虚函数表里面查询，会额外没必要的增加调用虚函数的成本。

### 构造函数和析构函数抛异常

构造函数抛出异常，会导致析构函数不能被调用，但对象本身已申请到的内存资源会被系统释放（已申请到资源的内部成员变量会被系统依次逆序调用其析构函数）。

析构函数抛出异常，会导致程序过早结束或出现不明确的行为。

### C++如何实现多态？虚表指针是什么时候被初始化的？实例化一个对象需要那几个阶段？

基类指针调用基类和派生类的同名虚函数。

* vtable 是每个 class 类型一个，不是每个对象一个。vtable 的大小（长度）跟这个 class 的虚函数总数（继承和自己新增）正相关。
* vptr 是每个对象一个，vptr 大小是固定的，跟虚函数多少无关。
* 对象的 vptr 在构造和析构的时候可能会变，指向不同的 vtable。对象构造完就不会变了。

[C++ 中的虚函数 (表) 实现机制以及用 C 语言对其进行的模拟实现](https://blog.twofei.com/496/)

### 虚函数类的对象去memoryset内存清零，有什么问题；虚表在哪里存储

1. 破坏虚函数表，后续对虚函数的调用都将出现异常

2. 含(string, list, set, map 等) 时会破坏对象的内存

虚函数表由编译器在编译时生成，保存在.rdata 只读数据段

## 模板

### C++ 偏特化

[C++ 模板的偏特化与全特化](https://harttle.land/2015/10/03/cpp-template.html)

### 元编程，type_trait的理解

TODO

## STL

### vector底层原理，resize和reserve方法原理

### vector实现

一段连续的线性内存空间。
使用 3 个迭代器（可以理解成指针）来表示的。

vector 容器扩容时，不同的编译器申请更多内存空间的量是不同的。以 VS 为例，它会扩容现有容器容量的 50%。

### `remove`方法和`erase`方法

`vector`中的`remove`的作用是将等于`value`的元素放到`vector`的尾部，但并不减少`vector`的`size`

`vector`中`erase`的作用是删除掉某个位置`position`或一段区域（begin, end) 中的元素，减少其size

`list`容器中的`remove` 成员函数，原型是`void remove (const value_type& val);` 作用是删除`list`中值与`val`相同的节点，释放该节点的资源。而`list`容器中的`erase`成员函数，原型是`iterator erase (iterator position);` 作用是删除`position`位置的节点。考虑到 `list::erase` 是与位置有关，故`erase`还存在API:  `iterator erase (iterator first, iterator last);`

对于`set`来说，只有`erase` API，没有`remove` API。 `erase` 的作用是把符合要求的元素都删掉。

* `void erase (iterator position);`

* `size_type erase (const value_type& val);`

* `void erase (iterator first, iterator last);`

综上所述，`erase`一般是要释放资源，真正删除元素的，而`remove`主要用在`vector`中，用于将不符合要求的元素移到容器尾部，而并不删除不符合要求的元素。

[STL：remove和erase区别](https://www.cnblogs.com/buptlyn/p/4379212.html)

### map的实现？与哈希表区别？

hash_map 需要 hash 函数，等于函数；map 需要比较函数。

hash_map 采用 hash 表存储，map 一般采用红黑树 (RB Tree) 实现。

选择容器三个因素：查找速度，数据量，内存使用。

### map 底层结构

map底层使用的是红黑树实现，**红黑树牺牲了 avl 的完全平衡性减少了维持平衡和需要的旋转次数**，使得在插入和删除市最多只旋转3次（插入两次）。使得红黑树在插入和删除时更快。并且查找时间也是非常快的。

map 的下标运算符 `[]` 的作用是：将关键码作为下标去执行查找，并返回对应的值；如果不存在这个关键码，就将一个具有该关键码和值类型的默认值的项插入这个 map。

### map和set的区别

map 和 set 底层都是采用的红黑树实现的，两者最大的区别在于：map存储的是键值对，而 set 中每个元素只存储一个值，所以 map 可以通过下标访问，set 不能；另外 set 的迭代器是 `const` 的，不能通过迭代器修改存储的值，map 可以通过迭代器修改 value 的值，不能修改key 的值，原因就是 set 和 map 都是通过 key 排序的。

### map 遍历删除所有元素 迭代器失效问题

迭代器相当于是容器上的指针，容器可以自己管理内存，因此迭代器可能失效。

使用下面 2 种正确方法:

* 使用删除元素之前的迭代器定义下一个元素
* 使用 `erase()` 返回下一个元素的迭代器

### std::sort

对要排序的元素数目有一个阈值，如果大于该阈值则是用快排，如果小于阈值则用插入排序。

### allocator了解吗

STL 的分配器用于封装 STL 容器在内存管理上的底层细节。在 C++ 中，其内存配置和释放如下：
new 运算分两个阶段：(1)调用 `::operator new` 配置内存;(2)调用对象构造函数构造对象内容

delete 运算分两个阶段：(1)调用对象希构函数；(2)掉员工 `::operator delete` 释放内存

为了精密分工，STL allocator 将两个阶段操作区分开来：内存配置有`alloc::allocate()` 负责，内存释放由 `alloc::deallocate()` 负责；对象构造由`::construct()` 负责，对象析构由 `::destroy()` 负责。

同时为了提升内存管理的效率，减少申请小内存造成的内存碎片问题，SGI STL采用了 **两级配置器**，当分配的空间大小超过 128B 时，会使用第一级空间配置器；当分配的空间大小小于 128B 时，将使用第二级空间配置器。第一级空间配置器直接使用 `malloc()`、`realloc()`、`free()` 函数进行内存空间的分配和释放，而第二级空间配置器采用了内存池技术，通过空闲链表来管理内存。

* [C++ allocator类学习理解](https://www.cnblogs.com/SimonKly/p/7819122.html)
* [C++中的allocator类（内存分配器）](https://blog.csdn.net/u012333003/article/details/22104939)
* [C++中为什么要有allocator类？](https://www.zhihu.com/question/274802525)
* [C++ allocator 自定义指南](http://www.mamicode.com/info-detail-2341387.html)
* [STL源码剖析 提炼总结：空间配置器(allocator)](https://zhuanlan.zhihu.com/p/34725232)

### 介绍C++内存配置器

[c++ STL（六 空间配置器、内存配置器）](https://www.cnblogs.com/xietianjiao/p/12344339.html)
[c++ stl 内存配置器](https://www.cnblogs.com/xietianjiao/p/12344098.html)
[STL库的内存配置器(allocator)](https://www.cppentry.com/bencandy.php?fid=49&id=149890)

## 智能指针

最简单的智能指针就是使用 RAII 资源获取即初始化技术，在对象构造时申请内存，在析构时释放内存，另外还要重载 `*` 和 `->` 运算符，使其能够像指针一样使用。

### 一个unique_ptr怎么赋值给另一个unique_ptr对象？（std::move）

* 接受 release 后的指针
* move

一般来说，unique_ptr 被销毁时（如离开作用域），对象也就自动释放了，也可以通过其他方式下显示释放对象。如：

```cpp
up = nullptr; //置为空，释放up指向的对象
up.release(); //放弃控制权，返回裸指针，并将up置为空
up.reset(); //释放up指向的对象
```

### shared_ptr 指向同一地址

```c++
int *sp = new int{10};
shared_ptr<int> sp1(sp);
shared_ptr<int> sp2(sp);
```

一个地址被连个智能指针所引用，引用计数都是分别计数，所以在释放的时候会释放两次。

### 类获取到自己的`shared_ptr`

在`class`内部,获得`this`指针的`shared_ptr`,需要`class`继承`std::enable_shared_from_this`

[std::enable_shared_from_this 有什么意义？](https://www.zhihu.com/question/30957800)

[C++智能指针的enable_shared_from_this和shared_from_this机制](https://blog.csdn.net/QIANGWEIYUAN/article/details/88973735)

[C++11新特性之十：enable_shared_from_this](https://blog.csdn.net/caoshangpa/article/details/79392878)

#### weak_ptr 作用

## 内存管理

### Linux进程地址空间布局

[linux 虚拟地址空间布局](https://www.cnblogs.com/clover-toeic/p/3754433.html)

### sizeof 一个空类

为 1，因为 C++ 标准规定类的大小不为 0

### 访问 NULL 指针

每个进程空间的 0x0 虚拟地址开始的线性区 (memory region) 都会被映射到一个用户态没有访问权限的页上

### 堆和栈，为什么栈更快

栈快,系统控制释放，内存连续，无碎片

### 字节对齐

* 结构体第一个成员的地址和结构体的首地址相同
* 结构体每个成员地址相对于结构体首地址的偏移量（offset）是该成员大小的整数倍，如果不是则编译器会在成员之间添加填充字节（internal adding）。
* 结构体总的大小要是其成员中最大 size 的整数倍，如果不是编译器会在其末尾添加填充字节。

[计算结构体的大小](https://blog.csdn.net/weixin_42423872/article/details/81229249)

### malloc 函数

#### `malloc` 内存对齐

[malloc(malloc在32位编译系统中分配的地址会8字节对齐，64为编译系统中会8或者16字节对齐)](https://blog.csdn.net/sweetfather/article/details/79798962)
[malloc内存分配字节对齐问题](https://blog.csdn.net/shemangui/article/details/50459102?locationNum=1)
[malloc分配内存进行对齐的操作](https://www.cnblogs.com/sigma0/p/10837760.html)
[用malloc分配内存的字节对齐，指针对齐](https://www.douban.com/note/643194488/)
[malloc会保证内存对齐吗？](http://cn.voidcc.com/question/p-cdlgkjum-sm.html)

#### malloc 和 mmmap 的底层实现？malloc 分配的是什么？

linux 系统向用户提供申请的内存有 brk (sbrk) 和 mmap 函数。

mmap 函数第一种用法是映射磁盘文件到内存中；而 malloc 使用的 mmap 函数的第二种用法，即匿名映射，匿名映射不映射磁盘文件，而是向映射区申请一块内存。

malloc 采用的是内存池的实现方式，malloc 内存池实现方式更类似于 STL 分配器和 memcached 的内存池，先申请一大块内存，然后将内存分成不同大小的内存块，然后用户申请内存时，直接从内存池中选择一块相近的内存块即可。

malloc 利用 chunk 结构来管理内存块，malloc 就是由不同大小的 chunk 链表组成的。malloc 会给用户分配的空间的前后加上一些控制信息，用这样的方法来记录分配的信息，以便完成分配和释放工作。

[malloc 实现原理](http://luodw.cc/2016/02/17/malloc/)

#### mmap在用户区还是内核区？为什么快速？

#### 如果malloc 1G的内存，将其512M位置的地方赋值为1，此时实际分配的物理内存会是512M吗？

不会


### new

#### new 的对象 free

不可以，这是未定义行为。

new/delete 会调用 operator new/delete 函数，而每个类可以自己定义 operator new/delete 函数。

C++ 默认的内存分配器，未必是 malloc/free 使用的那个。

#### new函数失败

抛出 `bad_alloc` 异常，可以通过 try catch 捕捉。或者通过 `set_new_handler` 函数设置函数指针处理失败后的异常。  

在 new 时，添加 `std::nothrow` 抑制异常抛出，返回空指针。  

```cpp
int* p = new (std::nothrow) int; // 这样如果 new 失败了，就不会抛出异常，而是返回空指针
```

当 operator new 抛出异常前，会调用 new-handler. 使用 set_new_handler 设置 new-handler.
set_new_handler 的参数是个指针，返回值也是个指针，返回替换之前的 new-handler.

### new 和 malloc 的区别

两者都是用于动态分配堆内存。区别是：

* new 是操作符不是函数，在分配的内存的同时，会执行构造函数，malloc 是从库函数；
* new 操作符会根据类型自动计算要分配的内存大小，malloc 要通过参数指定；
* new 操作符的返回值是对象类型的指针，不需要进行指针类型转换，而malloc 返回的是void * 万能指针，需要转换成指定类型的指针；
* new 内存分配失败时，会抛出 bac_alloc 异常。malloc 分配内存失败时返回 NULL


### 无锁编程 atomic

[C++11原子操作与无锁编程](https://www.jianshu.com/p/3e122ee901c5)

## 新技术

### lambda

仿函数(functor)就是重定义了成员函数 operator() 的一种自定义类型对象。

lambda 表达式的返回值就是一个匿名的仿函数。

默认情况下， lambda函数总是一个const函数，mutable可以取消其常量性。在使用该修饰符时，参数列表不可省略

* []：没有任何函数对象参数。
* [=]：函数体内可以使用 Lambda 所在范围内 **所有可见的局部变量** （包括 Lambda 所在类的 this），并且是 **值传递** 方式（相当于编译器自动为我们按值传递了所有局部变量）。
* [&]：函数体内可以使用 Lambda 所在范围内所有可见的局部变量（包括 Lambda 所在类的 this），并且是 **引用传递** 方式（相当于是编译器自动为我们按引用传递了所有局部变量）。
* [this]：函数体内可以使用 lambda **所在类中的成员变量**。
* [a]：将 a 按值进行传递。按值进行传递时，函数体内不能修改传递进来的 a 的拷贝，因为默认情况下函数是 const 的，要修改传递进来的拷贝，可以添加 mutable 修饰符。
* [&a]：将 a 按引用进行传递。

### 类型转换

* const_cast 去掉类型的const或volatile属性
* static_cast 无条件转换，静态类型转换
* dynamic_cast 有条件转换，动态类型转换，运行时检查类型安全（转换失败返回NULL）
* reinterpret_cast 仅重新解释类型，但没有进行二进制的转换

去const属性用const_cast

基本类型转换用static_cast

多态类之间的类型转换用dynamic_cast

不同类型的指针类型转换用reinterpret_cast

#### dynamic_cast

RTTI(Run Time Type Identification) 即通过运行时类型识别，程序能够使用基类的指针或引用来检查着这些指针或引用所指的对象的实际派生类型

C++ 提供了两种方式来支持 RTTI，dynamic_cast 是其中一种，另一种是 typeid()。

### 闭包

[c++11 闭包的实现](https://www.cnblogs.com/lsgxeva/p/7788259.html)

[c++11 lambda表达式](https://www.cnblogs.com/lsgxeva/p/7788555.html)

### std::function

### std::bind

[c++11 lambda表达式](https://www.cnblogs.com/lsgxeva/p/7788555.html)

### 右值引用 和 move

### SFINAE 技术

SFINAE 是 C++ 模板编译的一个原则，全名叫做 Substitution Failure Is Not An Error

C++ 编译过程中，如果模板实例化后的某个模板函数（模板类）对该调用无效，那么将继续寻找其他重载决议，而不是引发一个编译错误。

TODO

### `std::forward`的作用

**完美转发**，利用应用的折叠原则：`T& && -> T&, T&& && -> T&&`来完成完美转发。

### c++ 11中union的变量可以为非POD类型吗？

c++11之前是不允许的，但是在c++11之后消除了这个限制，但是如果是union包含非POD类型，则需要自定义默认构造函数。

[C++ union(只支持基础类型)](https://blog.csdn.net/wangeen/article/details/8439306)
[c++11中，含有类类型的union](https://blog.csdn.net/ml422524/article/details/77941546)
[c++ - 关于 C++ 非POD联合的c++11问题](https://kb.kutu66.com/others/post_12551674)
[c++中POD类型和non-POD类型](https://www.cnblogs.com/time-is-life/p/9629111.html)
[C++11非受限联合体（union）](http://c.biancheng.net/view/7165.html)

### 垃圾回收机制

三种基本的垃圾收集算法

1. 引用计数算法
2. Mark & Sweep 算法 标记阶段和回收阶段组成，标记阶段标记出根节点所有可达的对节点，清除阶段释放每个未被标记的已分配块。
3. 节点复制算法

C++ 使用 `RAII` 手动管理资源

## 其他

### `std::move` 失效

[C++ lambda 内 std::move 失效问题的思考](https://www.cyhone.com/articles/why-move-no-work-in-lambda/)
如果`std::move`的参数是一个常量引用，则会造成失效。

### 用户态到内核态的切换，两者怎么进行通信

[用户态与内核态之间的切换](https://blog.csdn.net/u012333003/article/details/29384807)

[内核态和用户态的区别](https://www.cnblogs.com/viviwind/archive/2012/09/22/2698450.html)

[Linux用户态与内核态通信的几种方式](https://cloud.tencent.com/developer/article/1454965)

[Linux探秘之用户态与内核态](https://www.cnblogs.com/bakari/p/5520860.html)

[用户态/内核态/线程/协程](https://blog.nowcoder.net/n/5541fdad534649c2933937a7af0be1ec)

### gdb多线程调试

TODO
