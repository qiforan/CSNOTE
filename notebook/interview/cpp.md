# 面试

## c/c++ 基础

### 1. map的实现？与哈希表区别？

hash_map 需要 hash 函数，等于函数；map 需要比较函数。

hash_map 采用 hash 表存储，map 一般采用红黑树 (RB Tree) 实现。

选择容器三个因素：查找速度，数据量，内存使用。

### 2. vector实现

一段连续的线性内存空间。
使用 3 个迭代器（可以理解成指针）来表示的。

vector 容器扩容时，不同的编译器申请更多内存空间的量是不同的。以 VS 为例，它会扩容现有容器容量的 50%。

### 3. C++面向对象的三种特性？

封装、继承、多态。

### 4. C++继承和组合？你在实际项目中是怎么使用的？什么情况下使用继承？什么情况下使用组合？

类继承通常为 “白箱复用”，对象组合通常为 “黑箱复用”。

继承在某种程度上破坏了封装性，子类父类耦合度高；而对象组合则只要求被组合的对象具有良好定义的接口，耦合度低。

### 5. C++构造函数可以是虚函数吗？为什么？

构造函数不能是虚函数。

从 C++ 的视角来看，我们只能在编译时明确我们要构造的类的类型，才可以拿到这个类的构造函数，再使用这个构造函数构造我们想要的类，虚的构造函数从这个角度来看就是一个悖论。

### 6. C++析构函数可以是虚函数吗？为什么要将析构函数设置为虚函数？

析构函数可以且常常是虚函数。如果不是虚函数，则使用时可能存在内存泄漏的问题。

情形：用基类指针调用析构函数，使派生类的内存泄露。

### 7. C++如何实现多态？虚表指针是什么时候被初始化的？实例化一个对象需要那几个阶段？

基类指针调用基类和派生类的同名虚函数。

* vtable 是每个 class 类型一个，不是每个对象一个。vtable 的大小（长度）跟这个 class 的虚函数总数（继承和自己新增）正相关。
* vptr 是每个对象一个，vptr 大小是固定的，跟虚函数多少无关。
* 对象的 vptr 在构造和析构的时候可能会变，指向不同的 vtable。对象构造完就不会变了。

[C++ 中的虚函数 (表) 实现机制以及用 C 语言对其进行的模拟实现](https://blog.twofei.com/496/)

### 8. C++偏特化？

[C++ 模板的偏特化与全特化](https://harttle.land/2015/10/03/cpp-template.html)

### 9. 重载、重写、覆盖？

函数同名不同参

派生类的函数屏蔽了与其同名的基类函数

派生类函数覆盖基类函数

### 10. static关键字的作用？（要全面）怎么实现的？

* 在函数体外（全局作用域），限制函数或者对象的使用范围为本文件；
* 在函数体内的静态变量，声明周期为整程序运行周期；
* 类的静态方法与静态成员

[C++ static 的用法](https://www.cnblogs.com/XuChengNotes/p/10403523.html)

### 11. inline和宏定义的区别？inline是如何实现的？宏定义是如何实现的？

[C++ inline和#define宏的区别](https://www.cnblogs.com/yanwei-wang/p/8073111.html)

### 12. 指针和引用的区别？怎么实现的？

[引用和指针的区别](https://www.zhihu.com/question/37608201)

### 13. 字节对齐？结构体大小计算？然后又扯到位域？

* 结构体第一个成员的地址和结构体的首地址相同
* 结构体每个成员地址相对于结构体首地址的偏移量（offset）是该成员大小的整数倍，如果不是则编译器会在成员之间添加填充字节（internal adding）。
* 结构体总的大小要是其成员中最大size的整数倍，如果不是编译器会在其末尾添加填充字节。

[计算结构体的大小](https://blog.csdn.net/weixin_42423872/article/details/81229249)

### 14. allocator了解吗

* [C++ allocator类学习理解](https://www.cnblogs.com/SimonKly/p/7819122.html)
* [C++中的allocator类（内存分配器）](https://blog.csdn.net/u012333003/article/details/22104939)
* [C++中为什么要有allocator类？](https://www.zhihu.com/question/274802525)
* [C++ allocator 自定义指南](http://www.mamicode.com/info-detail-2341387.html)
* [STL源码剖析 提炼总结：空间配置器(allocator)](https://zhuanlan.zhihu.com/p/34725232)

### 15. map和unordered_map的底层实现？目前map支持 `map[10] = 20` 这种操作，其底层怎么实现的？和insert有什么区别？

map 的下标运算符 [] 的作用是：将关键码作为下标去执行查找，并返回对应的值；如果不存在这个关键码，就将一个具有该关键码和值类型的默认值的项插入这个 map。

都是调用红黑二叉树 `insert_unique()` 函数来完成

### 16. map如何遍历删除所有元素？迭代器失效？

迭代器相当于是容器上的指针，容器可以自己管理内存，因此迭代器可能失效。

使用下面 2 种正确方法:

* 使用删除元素之前的迭代器定义下一个元素
* 使用 `erase()` 返回下一个元素的迭代器

### 17. 一个unique_ptr怎么赋值给另一个unique_ptr对象？（std::move）

* 接受 release 后的指针
* move

一般来说，unique_ptr 被销毁时（如离开作用域），对象也就自动释放了，也可以通过其他方式下显示释放对象。如：

```cpp
up = nullptr; //置为空，释放up指向的对象
up.release(); //放弃控制权，返回裸指针，并将up置为空
up.reset(); //释放up指向的对象
```

### 18. 下面代码有什么问题？引用计数如何变化？

```c++
int *sp = new int{10};
shared_ptr<int> sp1(sp);
shared_ptr<int> sp2(sp);
```

一个地址被连个智能指针所引用，引用计数都是分别计数，所以在释放的时候会释放两次。

### 19. c语言的函数调用栈底层详细说说？  

[C语言函数调用栈(一)](https://www.cnblogs.com/clover-toeic/p/3755401.html)
[C语言函数调用栈(二)](https://www.cnblogs.com/clover-toeic/p/3756668.html)
[c语言函数调用过程中栈的工作原理理解](https://blog.csdn.net/qq_31567335/article/details/84782202)
[C语言函数调用的底层机制](https://blog.csdn.net/maochengtao/article/details/61630370)

### 20. static变量存放在哪里？什么时候分配的内存？

静态变量属于静态存储方式，其存储空间为内存中的静态数据区.

### 24. 计算机基础

short类型占几个字节，int 类型占几个字节，short和int相加时会有隐式类型转换，对于补码来说，这个转换是在short的高字节位填充什么？把一个负数转换为补码形式最简单的方法应该是怎么做？

在32位环境中，char 8位，short 16位，int 32位，long 32位，int*（泛指指针）32位，long long 32位，float 32位，double 64位

在64位环境中，char 8位，short 16位，int 32位，long 64位，int*（泛指指针）64位，long long 32位，float 32位，double 64位

在类中，如果什么都没有，则类占用1个字节，一旦类中有其他的占用空间成员，则这1个字节就不在计算之内，如一个类只有一个int则占用4字节而不是5字节。

如果只有成员函数，则还是只占用1个字节，因为类函数不占用空间

虚函数因为存在一个虚函数表，需要4个字节，数据成员对象如果为指针则为4字节，注意有字节对齐，如果为13字节，则进位到16字节空间。

### 25. 带参数的宏定义怎么写？

参数表中的参数之间用逗号分隔，字符序列中应包含参数表中的参数。在定义带参数的宏时，宏名标识符与左圆括号之间不允许有空白符

使用 #把宏参数变为一个字符串，用 ## 把两个宏参数贴合在一起

### 26. 局部变量和全局变量的作用范围和生存周期，外部变量要在另一个源文件中使用要怎么做？加static之后会怎么样？

### 27. new的对象可以free吗？为什么？

不可以，这是未定义行为。

new/delete 会调用 operator new/delete 函数，而每个类可以自己定义 operator new/delete 函数。

C++ 默认的内存分配器，未必是 malloc/free 使用的那个。

### 29. map底层，和avl比有什么优势

map底层使用的是红黑树实现，**红黑树牺牲了avl的完全平衡性减少了维持平衡和需要的旋转次数**，使得在插入和删除市最多只旋转3次（插入两次）。使得红黑树在插入和删除时更快。并且查找时间也是非常快的。

### 34. c++析构函数，尽可能把你理解的析构函数介绍一下？

析构函数是为了对对象的一些资源进行释放，析构函数在一些具体的代码中要设置成为虚析构函数，先析构子类

### 37. 无锁编程 atomic，STL 空间配置器源码，shared_ptr源码

TODO

### 40. new函数失败怎么办

抛出 `bad_alloc` 异常，可以通过try catch捕捉。或者通过 `set_new_handler` 函数设置函数指针处理失败后的异常。  
再问：可以不抛出异常吗？  
答：可以，new时，添加std::nothrow  
三问，set_new_handler函数怎么实现的？  
具体函数实现我没看，不过我猜应该是通过设置signal或者sigaction捕捉信号函数，捕捉到异常的信号后，再用回调函数处理的。

C++ 里，如果 new 分配内存失败，默认是抛出 bad_alloc 异常。
也可抑制 new 抛出异常，返回空指针：

```cpp
int* p = new (std::nothrow) int; // 这样如果 new 失败了，就不会抛出异常，而是返回空指针
```

当 operator new 抛出异常前，会调用 new-handler. 使用 set_new_handler 设置 new-handler.
set_new_handler 的参数是个指针，返回值也是个指针，返回替换之前的 new-handler.

### 41. C++11的lambda是如何实现的，跟真正的仿函数在实现上有什么区别

[lambda表达式与仿函数](https://blog.csdn.net/quinta_2018_01_09/article/details/93763832)

[C++ 仿函数](https://blog.csdn.net/K346K346/article/details/82818801)

仿函数(functor)就是重定义了成员函数 operator() 的一种自定义类型对象。

lambda 表达式的返回值就是一个仿函数

### 42. dynamic_cast，解决什么问题，引用的情况下不成功返回什么

C++ 提供了两种方式来支持 RTTI，dynamic_cast 是其中一种，另一种是 typeid()。

### 43. C语言中printf中无限参数的问题，怎样实现？

[C语言中的可变参数（printf的实现原理）](https://blog.csdn.net/yzy1103203312/article/details/80808741)
[C语言实现printf函数，即参数可变函数原理](https://blog.csdn.net/gengyiping18/article/details/50603326)

### 45. ++i， i++是否是原子操作

[i++和++i是否为原子操作](https://blog.csdn.net/u010214092/article/details/50634430)
[i++是否原子操作](https://www.cnblogs.com/lxd2502/p/4648020.html)

### 47. 虚函数类的对象去memoryset内存清零，有什么问题；虚表在哪里存储

1. 破坏虚函数表，后续对虚函数的调用都将出现异常

2. 含(string, list, set, map 等) 时会破坏对象的内存

虚函数表由编译器在编译时生成，保存在.rdata 只读数据段

### 50. 闭包

[c++11 闭包的实现](https://www.cnblogs.com/lsgxeva/p/7788259.html)

[c++11 lambda表达式](https://www.cnblogs.com/lsgxeva/p/7788555.html)

### 51. std::function可以封装哪些实体，可以封装函数对象吗？

[c++11 闭包的实现](https://www.cnblogs.com/lsgxeva/p/7788259.html)

### 52. lambda表达式介绍一下，可以引用外部变量吗？

[C++ lambda表达式及其原理](https://blog.csdn.net/weixin_39640298/article/details/84996642)

[C++lambda表达式](https://blog.csdn.net/Sum7mer/article/details/89636651)

### 53. std::bind和lambda表达式区别？

[c++11 闭包的实现](https://www.cnblogs.com/lsgxeva/p/7788259.html)
[c++11 lambda表达式](https://www.cnblogs.com/lsgxeva/p/7788555.html)

### 54. 为什么需要this指针

其作用就是指向成员函数所作用的对象

### 55. 自增运算符的步骤（内存，寄存器），有两个线程分别自增100次，问最后结果的最大最小值？

[面试---i++在两个线程分别执行100次，最大值和最小值分别多少](https://blog.csdn.net/will130/article/details/48714343?locationNum=5)

### 57. c++使用c函数一样吗，c++编译和c编译有什么不同

[C/C++：函数的编译方式与调用约定以及extern “C”的使用](https://www.cnblogs.com/qinfengxiaoyue/archive/2013/02/04/2891908.html)
[C/C++ 编译与函数的深度理解](https://www.jianshu.com/p/fb4cf4d07a18)

### 58. gdb多线程调试

TODO

### 60. switch的case里为何不能定义变量

[switch-case内不能定义变量？](https://www.cnblogs.com/Younger-Zhang/p/11316290.html)
[switch - case 中不能定义变量 的解决办法](https://blog.csdn.net/qq_35865125/article/details/104739997)
[请教switch内部的变量定义问题？](https://www.zhihu.com/question/23051685)

### 61. 如果可以确定一个类没有子类，这个类的析构函数还有必要是虚函数吗

没有必要，因为一旦设置成虚函数，则对象中一定会有虚函数表占用额外的存储空间，况且虚函数的调用需要从虚函数表里面查询，会额外没必要的增加调用虚函数的成本。

### 63. STL算法的`remove`方法和`erase`方法的区别

`vector`中的`remove`的作用是将等于`value`的元素放到`vector`的尾部，但并不减少`vector`的`size`

`vector`中`erase`的作用是删除掉某个位置`position`或一段区域（begin, end)中的元素，减少其size

`list`容器中的`remove` 成员函数，原型是v`oid remove (const value_type& val);`作用是删除`list`中值与`val`相同的节点，释放该节点的资源。而`list`容器中的`erase`成员函数，原型是`iterator erase (iterator position);`作用是删除`position`位置的节点。考虑到`list::erase`是与位置有关，故`erase`还存在API:  `iterator erase (iterator first, iterator last);`

对于`set`来说，只有`erase` API，没有`remove` API。 `erase` 的作用是把符合要求的元素都删掉。

* `void erase (iterator position);`

* `size_type erase (const value_type& val);`

* `void erase (iterator first, iterator last);`

综上所述，`erase`一般是要释放资源，真正删除元素的，而`remove`主要用在`vector`中，用于将不符合要求的元素移到容器尾部，而并不删除不符合要求的元素。

引用[STL：remove和erase区别](https://www.cnblogs.com/buptlyn/p/4379212.html)

### 64. SFINAE 技术

SFINAE 是 C++ 模板编译的一个原则，全名叫做 Substitution Failure Is Not An Error

C++ 编译过程中，如果模板实例化后的某个模板函数（模板类）对该调用无效，那么将继续寻找其他重载决议，而不是引发一个编译错误。

TODO

### 65. 元编程，type_trait的理解

TODO

### 68. `std::forward`的作用

完美转发，利用应用的折叠原则：`T& && -> T&, T&& && -> T&&`来完成完美转发。

### 69. 为什么系统调用比普通函数调用消耗大？

切换用户栈，内核栈，保存寄存器信息，这些只是基本开销。还有页表切换，不同用户的页表是不一样的，系统调用为了服务不同用户，需要切换页表。切换页表意味着cpu缓存失效。而且内核空间跟用户空间地址空间相差很大，指令预测系统也会失效。系统调用需要在用户空间和内核空间进行切换，普通函数调用只是同一个空间调用，只是压栈这一点开销，相对于系统调用这点开销并不算什么，甚至函数式编程的压栈开销都没有。

[https://www.zhihu.com/question/400440365](https://www.zhihu.com/question/400440365)

### 70. 可以直接交换两个同类型对象的内存数据吗？

c/c++中没有类似的命令与操作不过可以自己重载与函数等等从语义上实现交换

### 71. c++ 11中union的变量可以为非POD类型吗？

c++11之前是不允许的，但是在c++11之后消除了这个限制，但是如果是union包含非POD类型，则需要自定义默认构造函数。

[C++ union(只支持基础类型)](https://blog.csdn.net/wangeen/article/details/8439306)
[c++11中，含有类类型的union](https://blog.csdn.net/ml422524/article/details/77941546)
[c++ - 关于 C++ 非POD联合的c++11问题](https://kb.kutu66.com/others/post_12551674)
[c++中POD类型和non-POD类型](https://www.cnblogs.com/time-is-life/p/9629111.html)
[C++11非受限联合体（union）](http://c.biancheng.net/view/7165.html)

### 72. C++垃圾回收机制

[C++中垃圾回收机制中几种经典的垃圾回收算法](https://blog.csdn.net/u012611878/article/details/78947267)
[C++垃圾回收机制](https://www.cnblogs.com/blfshiye/p/3764059.html)
[C++为什么不加入垃圾回收机制](https://blog.csdn.net/yeahhook/article/details/6796242)
[C/C++中几种经典的垃圾回收算法](https://www.cnblogs.com/lidabo/p/3487045.html)
[什么情况下 C++ 需要垃圾处理机制？](https://www.zhihu.com/question/308638046)

### 73. 浮点数怎么表示？大概说了下ieee754,浮点数表示范围连续吗？为什么不连续？

[浮点数的表示范围](http://www.cppblog.com/jianjianxiaole/articles/float.html)

### 74. `volatile`

[C/C++ Volatile关键词深度剖析](https://www.cnblogs.com/god-of-death/p/7852394.html)
[C++中volatile的作用](https://blog.csdn.net/weixin_41656968/article/details/80958973)

### 75. 那如何实现对一个常量进行引用

### 76. vector底层原理，resize和reserve方法原理

### 77. C++中异常处理中try-catch的实现机制,问假设一个try后有多个catch，catch的异常类型相同，是怎么匹配到对应的catch的

[C++异常处理（try catch throw）完全攻略](http://c.biancheng.net/view/422.html)
[C++异常机制的实现方式和开销分析](http://www.baiy.cn/doc/cpp/inside_exception.htm)
[异常](http://www.baiy.cn/doc/cpp/index.htm#%E4%BB%A3%E7%A0%81%E9%A3%8E%E6%A0%BC%E4%B8%8E%E7%89%88%E5%BC%8F_%E5%BC%82%E5%B8%B8)
[C++异常处理机制](https://blog.csdn.net/caihaitao2000/article/details/79827857)

### 80. 调用`malloc`的时候要求 8 bytes 内存对齐，怎么处理？

[malloc(malloc在32位编译系统中分配的地址会8字节对齐，64为编译系统中会8或者16字节对齐)](https://blog.csdn.net/sweetfather/article/details/79798962)
[malloc内存分配字节对齐问题](https://blog.csdn.net/shemangui/article/details/50459102?locationNum=1)
[malloc分配内存进行对齐的操作](https://www.cnblogs.com/sigma0/p/10837760.html)
[用malloc分配内存的字节对齐，指针对齐](https://www.douban.com/note/643194488/)
[malloc会保证内存对齐吗？](http://cn.voidcc.com/question/p-cdlgkjum-sm.html)

### 81. 介绍C++内存配置器

[c++ STL（六 空间配置器、内存配置器）](https://www.cnblogs.com/xietianjiao/p/12344339.html)
[c++ stl 内存配置器](https://www.cnblogs.com/xietianjiao/p/12344098.html)
[STL库的内存配置器(allocator)](https://www.cppentry.com/bencandy.php?fid=49&id=149890)

### 83. 考虑如下代码

```c++
class A {
    virtual void foo() = 0;
};
class B : public  A{
};
```

* `sizeof(A)`在 32 位的机器上  `sizeof(A)=4`

* 使用`class B`的话，后续可能会出现什么问题？（析构函数不是虚函数）

* 编译器为`class B`生成了哪些函数？有右值版本的函数吗？

### 84. 在c++11之后已经有了右值版本的`push_back()`

### 85. 类获取到自己的`shared_ptr`

在`class`内部,获得`this`指针的`shared_ptr`,需要`class`继承`std::enable_shared_from_this`

[std::enable_shared_from_this 有什么意义？](https://www.zhihu.com/question/30957800)
[C++智能指针的enable_shared_from_this和shared_from_this机制](https://blog.csdn.net/QIANGWEIYUAN/article/details/88973735)
[C++11新特性之十：enable_shared_from_this](https://blog.csdn.net/caoshangpa/article/details/79392878)、

### 86. sizeof 一个空类

为 1，因为 C++ 标准规定类的大小不为 0

### 87. 虚函数表指针通常存储在类对象的哪个位置?为什么

TODO

### 88. `std::move`失效

[C++ lambda 内 std::move 失效问题的思考](https://www.cyhone.com/articles/why-move-no-work-in-lambda/)
如果`std::move`的参数是一个常量引用，则会造成失效。

---

## 操作系统

### 内存管理

#### 1. malloc和mmap的底层实现？malloc分配的是什么？

linux 系统向用户提供申请的内存有 brk (sbrk) 和 mmap 函数。

mmap 函数第一种用法是映射磁盘文件到内存中；而 malloc 使用的 mmap 函数的第二种用法，即匿名映射，匿名映射不映射磁盘文件，而是向映射区申请一块内存。

malloc 采用的是内存池的实现方式，malloc 内存池实现方式更类似于 STL 分配器和 memcached 的内存池，先申请一大块内存，然后将内存分成不同大小的内存块，然后用户申请内存时，直接从内存池中选择一块相近的内存块即可。

malloc 利用 chunk 结构来管理内存块，malloc 就是由不同大小的 chunk 链表组成的。malloc 会给用户分配的空间的前后加上一些控制信息，用这样的方法来记录分配的信息，以便完成分配和释放工作。

[malloc 实现原理](http://luodw.cc/2016/02/17/malloc/)

#### 2. Linux进程地址空间布局

[linux 虚拟地址空间布局](https://www.cnblogs.com/clover-toeic/p/3754433.html)

#### 3. 页表是什么

虚拟地址到物理地址的转换

#### 5. 内存分配算法了解吗，比如说给你一个内存池，碎片和效率，策略

TODO

#### 6. 内存泄漏怎么规避呢？

#### 10. 内存中堆和栈那一种结构快?为什么栈更快?

栈快,系统控制释放，内存连续，无碎片

#### 13. Mmap在用户区还是内核区？为什么快速？

#### 14. 检测内存泄漏

#### 17. 访问NULL指针为什么会报错？编译期报错还是运行期报错？

每个进程空间的 0x0 虚拟地址开始的线性区 (memory region) 都会被映射到一个用户态没有访问权限的页上

#### 18. 如果malloc 1G的内存，将其512M位置的地方赋值为1，此时实际分配的物理内存会是512M吗？

#### 19. C++内存分配堆栈在内存中的大小,使用malloc函数，在32位机器上1G的物理内存能获取到的内存大小

#### 20. 用户态到内核态的切换，两者怎么进行通信

[用户态与内核态之间的切换](https://blog.csdn.net/u012333003/article/details/29384807)

[内核态和用户态的区别](https://www.cnblogs.com/viviwind/archive/2012/09/22/2698450.html)

[Linux用户态与内核态通信的几种方式](https://cloud.tencent.com/developer/article/1454965)

[Linux探秘之用户态与内核态](https://www.cnblogs.com/bakari/p/5520860.html)

[用户态/内核态/线程/协程](https://blog.nowcoder.net/n/5541fdad534649c2933937a7af0be1ec)
