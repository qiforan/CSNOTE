# GDB 速查

## 启动

```bash
# 正常启动
gdb obj
# 调试 core
gdb obj core
# 启动，需要 file 命令手动加载
gdb
# 启动 gdb 的文本界面
gdb -tui
```

## 运行

`run` 命令执行程序，直至遇到断点或结束。

```shell
r [args]                  # 运行，可携带参数
r < file                  # 运行，输入重定向
cont                      # 继续运行，简写 c
step                      # 单步进入，碰到函数会进去
step {count}              # 单步多少次
next                      # 单步跳过，碰到函数不会进入
next {count}              # 单步多少次
CTRL+C                    # 发送 SIGINT 信号，中止当前运行的程序
attach {process-id}       # 链接上当前正在运行的进程，开始调试
detach                    # 断开进程链接
finish                    # 结束当前函数的运行
until                     # 持续执行直到代码行号大于当前行号（跳出循环）
until {line}              # 持续执行直到执行到某行
kill                      # 杀死当前运行的函数
```

## 断点

`break` 命令可以给程序打断点，简写为 `b`

```shell
b main                    # 函数断点
b 101                     # 源代码的行号断点
b file.c:101

info break                # 列出断点信息

delete 1                  # 按编号删除断点
delete                    # 默认删除所有断点

clear                     # 删除当前断点
clear func                # 删除函数断点
clear line                # 删除行号断点

disable 2                 # 禁用某断点，但是不删除
enable 2                  # 允许某个之前被禁用的断点，让它生效

rbreak {regexpr}          # 匹配正则的函数前断点

tbreak function|line      # 临时断点
hbreak function|line      # 硬件断点

ignore {id} {count}       # 忽略某断点 N-1 次
condition {id} {expr}     # 条件断点，只有在条件生效时才发生
condition 2 i == 20       # 2号断点只有在 i == 20 条件为真时才生效
watch {expr}              # 对变量设置监视点
info watchpoints          # 显示所有观察点
catch exec                # 断点在exec事件，即子进程的入口地址
```

## 打印

`print` 命令可以打印变量，简写为 `p`. 也可以执行函数.

```shell
print {expression}        # 打印表达式，并且增加到打印历史
print /x {expression}     # 十六进制输出，print 可以简写为 p
print array[i]@count      # 打印数组范围
print $                   # 打印之前的变量
print $1                  # 输出打印历史里第一条
print ::gx                # 将变量可视范围（scope）设置为全局
print 'basic.c'::gx       # 打印某源代码里的全局变量，(gdb 4.6)
print /x &main            # 打印函数地址
x *0x11223344             # 显示给定地址的内存数据
x /nfu {address}          # 打印内存数据，n是多少个，f是格式，u是单位大小
x /10xb *0x11223344       # 按十六进制打印内存地址 0x11223344 处的十个字节
x/x &gx                   # 按十六进制打印变量 gx，x和斜杆后参数可以连写
x/4wx &main               # 按十六进制打印位于 main 函数开头的四个 long 
x/gf &gd1                 # 打印 double 类型
help x                    # 查看关于 x 命令的帮助
info locals               # 打印本地局部变量
info functions {regexp}   # 打印函数名称
info variables {regexp}   # 打印全局变量名称
ptype name                # 查看类型定义，比如 ptype FILE，查看 FILE 结构体定义
whatis {expression}       # 查看表达式的类型
set var = {expression}    # 变量赋值
display {expression}      # 在单步指令后查看某表达式的值
undisplay                 # 删除单步后对某些值的监控
info display              # 显示监视的表达式
show values               # 查看记录到打印历史中的变量的值 (gdb 4.0)
info history              # 查看打印历史的帮助 (gdb 3.5)
```