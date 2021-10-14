# Boost

## 1. 时间与日期

`timer` 库含三个组件，`timer`，`progress_timer` 和 `progress_display`.

`timer` 构造函数启动了计时工作，随时可以用 `elapsed()` 简单测量自对象构造所过去的时间，单位为秒。

## 2. 内存管理

### `unique_ptr`

由于 `auto_ptr` 复制时转移所有权，不符合复制的语义。C++11 去除了 `auto_ptr`，取而代之的是 `unique_ptr`，

## 3. 实用工具

### `noncopyable`

继承 `noncopyable` 可以实现一个禁止复制的类。

默认情况下，编译器会自动生成 __拷贝构造函数__ 和 __拷贝赋值函数__。

```c++
class do_not_copy: private noncopyable
{
    ...
};
```

