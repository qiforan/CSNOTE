# Python高级

## 线程

python的`thread`模块是比较底层的模块，python的`threading`模块是对`thread`做了一些包装的，可以更加方便的被使用

### 多线程的执行

```python
import threading
import time

def func():
    for i in range(100):
        print(i)
        time.sleep(1)

if __name__ == "__main__":
    t = threading.Thread(target=func)
    t.start()
```

说明：

- 主线程会等待所有的子线程结束后才结束
- 当调用`start()`时，才会真正的创建线程，并且开始执行
- 查看线程数量 `threading.enumerate()`

`threading`一般不直接使用，而是进行封装：继承`threading.Thread`，重写`run`方法

```python
import threading
import time

class MyThread(threading.Thread):
    def run(self):
        for i in range(3):
            time.sleep(1)
            msg = "{} @ {}".format(self.name, i)
            print(msg)

if __name__ == "__main__":
    for i in range(3):
        MyThread().start()
```

说明：

- 创建线程实例后，通过`Thread`类的`start`方法，可以启动该线程，交给虚拟机进行调度，当该线程获得执行的机会时，就会调用`run`方法执行
- 每个线程默认有一个名字，手动指定或由系统分配
- 线程的`run()`方法结束时该线程完成

### 给线程传递参数

```python
from threading import Thread
import time

def func(num,c=None):
    print(num,c)

if __name__ == "__main__":
    Thread(target=func, args=(1,),kwargs={"c":"c"}).start()
```

说明：

- 使用`args`参数以元组的形式传递位置参数
- 使用`kwargs`参数以字典的形式传递关键字参数

### 同步与互斥

`threading`模块中定义了`Lock`类

```python
# 创建锁
mutex = threading.Lock()

# 锁定
mutex.acquire()

# 释放
mutex.release()
```

## 进程

操作系统分配资源的基本单元

`multiprocessing`模块就是跨平台版本的多进程模块，提供了一个`Process`类来代表一个进程对象

```python
from multiprocessing import Process
import time, random, os

def func():
    while True:
        print(os.getpid()) # 获取当前进程的pid
        time.sleep(random.random())

if __name__ == "__main__":
    Process(target=func).start()
    while True:
        print(os.getpid())
        time.sleep(random.random())
```

Process创建的实例对象的常用方法：

- `start()`：启动子进程实例（创建子进程）
- `is_alive()`：判断进程子进程是否还在活着
- `join([timeout])`：是否等待子进程执行结束，或等待多少秒
- `terminate()`：不管任务是否完成，立即终止子进程

Process创建的实例对象的常用属性：

- `name`：当前进程的别名，默认为Process-N，N为从1开始递增的整数
- `pid`：当前进程的pid（进程号）

### 进程vs线程

略

### 进程间通信

使用`multiprocessing`模块的`Queue`实现多进程之间通信，`Queue`本身是一个消息列队

```python
from multiprocessing import Process,Queue
import os, time, random

def write(q):
    for value in ['A', 'B', 'C']:
        print("Put {} to queue".format(value))
        q.put(value)
        time.sleep(random.random())
    print("pid{} write completed".format(os.getpid()))


def read(q):
    while True:
        if not q.empty():
            value = q.get(True)
            print("Get {} from queue".format(value))
            time.sleep(random.random())
        else:
            break
    print("pid{} read completed".format(os.getpid()))

if __name__ == "__main__":
    q = Queue()
    pw = Process(target=write, args=(q,))
    pr = Process(target=read, args=(q,))
    pw.start()
    pw.join()
    pr.start()
    pr.join()
    print("")
    print("All done")
```

Queue实例对象的一些方法：

- `Queue.qsize()`：返回当前队列包含的消息数量；

- `Queue.empty()`：如果队列为空，返回True，反之False ；

- `Queue.full()`：如果队列满了，返回True,反之False；

- `Queue.get([block[, timeout]])`：获取一条消息并从队列中移除，`block`表示是否阻塞，若是，等待`timeout`后抛出异常

### 进程池Pool

`multiprocessing`模块提供的`Pool`方法

```python
from multiprocessing import Pool
import os, time, random

def func(msg):
    t_start = time.time()
    print("{} start, pid {}".format(msg, os.getpid()))
    time.sleep(random.random()*2)
    print(msg, " completd in {:.2f}s".format(time.time() - t_start))

if __name__ == "__main__":
    po = Pool(3)
    for i in range(10):
        po.apply_async(func,(i,))
    print('----start ----')
    po.close()
    po.join()
    print('----end ----')
```

`multiprocessing.Pool`常用函数解析：

- `apply_async(func[, args[, kwds]])` ：使用非阻塞方式调用func（并行执行，堵塞方式必须等待上一个进程退出才能执行下一个进程），args为传递给func的参数列表，kwds为传递给func的关键字参数列表；
- `close()`：关闭Pool，使其不再接受新的任务；
- `terminate()`：不管任务是否完成，立即终止；
- `join()`：主进程阻塞，等待子进程的退出， 必须在close或terminate之后使用；

如果要使用Pool创建进程，就需要使用`multiprocessing.Manager()`中的`Queue()`，而不是`multiprocessing.Queue()`

## 协程

### 迭代器

判断一个对象是否可迭代: `isinstance(obj,Iterable)`

可迭代对象通过`__iter__`方法向我们提供一个迭代器，我们在迭代一个可迭代对象的时候，实际上就是先获取该对象提供的一个迭代器，然后通过这个迭代器来依次获取对象中的每一个数据.

通过`iter()`函数获取这些可迭代对象的迭代器,使用`next()`函数来获取下一条数据

```python
class MyIterator(object):
    def __init__(self, mylist):
        self.mylist = mylist
        self.current = 0
    def __next__(self):
        if self.current < len(self.mylist.items):
            item = self.mylist.items[self.current]
            self.current += 1
            return item
        else:
            raise StopIteration
    def __iter__(self):# Python 要求迭代器本身可迭代
        return self

class MyList(object):
    def __init__(self):
        self.items = []
    def add(self, val):
        self.items.append(val)

    def __iter__(self):
        my_iterator = MyIterator(self)
        return my_iterator

if __name__ == "__main__":
    my_list = MyList()
    for i in range(5):
        my_list.add(i)
    for i in my_list:
        print(i)
```

一个实现了`__iter__`方法和`__next__`方法的对象，就是迭代器

### 生成器

使用了 `yield` 的函数被称为生成器，返回一个迭代器，用于迭代。

调用生成器运行的过程中，每次遇到 `yield` 时函数会暂停并保存当前所有的运行信息，返回 `yield` 的值, 并在下一次执行 `next()` 方法时从当前位置继续运行

```python
import sys

def fibonacci(n):
    a, b, count = 0, 1, 0
    while True:
        if count > n:
            return
        yield a
        a, b = b, a + b
        count += 1

if __name__ == "__main__":
    f = fibonacci(10)
    try:
        print(next(f))
    except StopIteration:
        sys.exit()
```

### 协程vs线程

使用含`yield`函数称之为协程，是另一种多任务的实现方式

- 线程有自己的缓存切换耗时间
- 切换协程只需要更改cpu上下文

### `greenlet`

python中的`greenlet`模块对其封装，从而使得切换任务变的更加简单

```python
from greenlet import greenlet
import time

def func1():
    while True:
        print("---A---")
        gr2.switch()
        time.sleep(0.5)

def func2():
    while True:
        print("---B---")
        gr1.switch()
        time.sleep(0.5)

gr1 = greenlet(func1)
gr2 = greenlet(func2)

gr1.switch()
```

### `gevent`

`gevent`能自动切换任务，当一个`greenlet`遇到IO(指的是input output 输入输出，比如网络、文件操作等)操作时，比如访问网络，就自动切换到其他的greenlet，等到IO操作完成，再在适当的时候切换回来继续执行

