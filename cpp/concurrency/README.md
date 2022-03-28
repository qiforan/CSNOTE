# C++ 并发

## 线程管理

每个程序至少有一个线程：执行 `main()` 函数的线程，其余线程有其各自的入口函数。

在为一个线程创建了一个 `std::thread` 对象后，需要等待这个线程结束；不过，线程需要先进行启动。

使用 C++ 线程库启动线程，可以归结为构造 std::thread` 对象：

```cpp
void do_some_work();
std::thread my_thread(do_some_work);
```

为了让编译器识别 `std::thread` 类，要包含 `<thread>` 头文件。`std::thread` 也可以用可调用类型构造。

启动线程后，需要明确是要等待线程结束，还是让其自主运行。如果 `std::thread` 对象销毁之前还没有做出决定，程序就会终止( `std::thread` 的析构函数会调用 `std::terminate()`)。

如果不等待线程，就必须保证线程结束之前，可访问的数据的 **有效性**。

这种情况很可能发生在线程还没结束，函数已经退出的时候，这时线程函数还持有函数局部变量的指针或引用。

如果需要等待线程，相关的 `std::thread` 实例需要使用 `join()`。

调用 `join()` 的行为，还清理了线程相关的存储部分，这样`std::thread` 对象将不再与已经完成的线程有任何关联。这意味着，一旦已经使用过 `join()`，`std::thread` 对象就不能再次加入了，当对其使用 `joinable()` 时，将返回 `false`。

使用 `detach()` 会让线程在后台运行，这就意味着主线程不能与之产生直接交互。

### 传递线程参数

向 `std::thread` 构造函数中的可调用对象，或函数传递一个参数很简单。

```cpp
void f(int i, std::string const& s);
std::thread t(f, 3, "hello");
```

需要特别要注意，当指向动态变量的指针作为参数传递给线程的情况，代码如下：

```cpp
void f(int i,std::string const& s);
void oops(int some_param)
{
  char buffer[1024]; // 1
  sprintf(buffer, "%i",some_param);
  std::thread t(f,3,buffer); // 2
  t.detach();
}
```

解决方案就是在传递到 `std::thread` 构造函数之前就将字面值转化为 `std::string` 对象。

还可能遇到相反的情况：期望传递一个非常量引用(但这不会被编译)，但整个对象被复制了。

```cpp
void update_data_for_widget(widget_id w,widget_data& data); // 1
void oops_again(widget_id w)
{
  widget_data data;
  std::thread t(update_data_for_widget,w,data); // 2
  display_status();
  t.join();
  process_widget_data(data);
}
```

解决办法是：使用 `std::ref` 将参数转换成引用的形式，从而可将线程的调用改为以下形式：

```cpp
std::thread t(update_data_for_widget,w,std::ref(data));
```

`std::thread` 的传参类似 `std::bind`

```cpp
class X
{
public:
  void do_lengthy_work();
};
X my_x;
std::thread t(&X::do_lengthy_work,&my_x); // 1
```

这段代码中，新线程将 `my_x.do_lengthy_work()` 作为线程函数；`my_x` 的地址①作为指针对象提供给函数。也可以为成员函数提供参数：`std::thread` 构造函数的第三个参数就是成员函数的第一个参数，以此类推。

每个 `std::thread` 实例都负责管理一个执行线程。执行线程的所有权可以在多个 `std::thread` 实例中互相转移，这是依赖于 `std::thread` 实例的可移动且不可复制性。不可复制保性证了在同一时间点，一个 `std::thread` 实例只能关联一个执行线程；可移动性使得开发者可以自己决定，哪个实例拥有实际执行线程的所有权。

```cpp
void some_function();
void some_other_function();
std::thread t1(some_function);            // 1
std::thread t2=std::move(t1);            // 2
t1=std::thread(some_other_function);    // 3
std::thread t3;                            // 4
t3=std::move(t2);                        // 5
t1=std::move(t3);                        // 6 赋值操作将使程序崩溃
```

为了确保线程程序退出前完成，下面的代码里定义了 `scoped_thread`类。

```cpp
class scoped_thread
{
  std::thread t;
public:
  explicit scoped_thread(std::thread t_):                 // 1
    t(std::move(t_))
  {
    if(!t.joinable())                                     // 2
      throw std::logic_error(“No thread”);
  }
  ~scoped_thread()
  {
    t.join();                                            // 3
  }
  scoped_thread(scoped_thread const&)=delete;
  scoped_thread& operator=(scoped_thread const&)=delete;
};
struct func; 
void f()
{
  int some_local_state;
  scoped_thread t(std::thread(func(some_local_state)));    // 4
  do_something_in_current_thread();
}                                                        // 5
```

### 决定线程数量

### 线程标识

线程标识类型为 `std::thread::id`，并可以通过两种方式进行检索。第一种，可以通过调用 `std::thread` 对象的成员函数 `get_id()` 来直接获取。如果 `std::thread` 对象没有与任何执行线程相关联，`get_id()` 将返回 `std::thread::type` 默认构造值，这个值表示“无线程”。第二种，当前线程中调用 `std::this_thread::get_id()` (这个函数定义在<thread>头文件中)也可以获得线程标识。

`std::thread::id` 对象可以自由的拷贝和对比,因为标识符就可以复用。如果两个对象的 `std::thread::id` 相等，那它们就是同一个线程，或者都“无线程”。如果不等，那么就代表了两个不同线程，或者一个有线程，另一没有线程。

这意味着允许程序员将其当做为容器的键值，做排序，或做其他方式的比较。

也可以使用输出流( `std::cout` )来记录一个 `std::thread::id` 对象的值。

```cpp
std::cout<<std::this_thread::get_id();
```

具体的输出结果是严格依赖于具体实现的，C++标准的唯一要求就是要保证ID比较结果相等的线程，必须有相同的输出。

## 线程间共享数据

解决恶性条件竞争最简单的办法就是对数据结构采用某种保护机制，确保只有进行修改的线程才能看到不变量被破坏时的中间状态。从其他访问线程的角度来看，修改不是已经完成了，就是还没开始。C++标准库提供很多类似的机制。

另一个选择是对数据结构和不变量的设计进行修改，修改完的结构必须能完成一系列不可分割的变化，也就是保证每个不变量保持稳定的状态，这就是所谓的无锁编程。

### 互斥量

C++ 中通过实例化 `std::mutex` 创建互斥量实例，通过成员函数 `lock()` 对互斥量上锁，`unlock()` 进行解锁。不过，实践中不推荐直接去调用成员函数，调用成员函数就意味着，必须在每个函数出口都要去调用 `unlock()`，也包括异常的情况。C++ 标准库为互斥量提供了一个 RAII 语法的模板类 `std::lock_guard`，在构造时就能提供已锁的互斥量，并在析构的时候进行解锁，从而保证了一个已锁互斥量能被正确解锁。

```cpp
#include <list>
#include <mutex>
#include <algorithm>
std::list<int> some_list;    // 1
std::mutex some_mutex;    // 2
void add_to_list(int new_value)
{
  std::lock_guard<std::mutex> guard(some_mutex);    // 3
  some_list.push_back(new_value);
}
bool list_contains(int value_to_find)
{
  std::lock_guard<std::mutex> guard(some_mutex);    // 4
  return std::find(some_list.begin(),some_list.end(),value_to_find) != some_list.end();
}
```
