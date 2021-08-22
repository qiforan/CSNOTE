# Python 笔记

## fluent Python 笔记

* [列表和元组](./list_tuple.ipynb)

* [字典和集合](./Dict&Set.ipynb)

* [文本和字节](./Texts&Bytes.ipynb)

* [函数](./First-Order-Object_Function.ipynb)

* [装饰器和闭包](./Decorator_&_Closure.ipynb)

## 进阶

* [多任务](./multi_task.md)

* [正则](./re.md)

## 编码转换

Python3的版本中，是使用Unicode编码类型对字符串进行编码的。

`ord()` 获取字符的整数表示
`chr()` 把编码转换为对应字符

在 `str` 里，一个字符可能占多个字节，因此我们需要以字节为单位的 `bytes`类型。
Python中的bytes类型用带b前缀的单引号，或者双引号来表示：

```python3
X = b'AaBbCc'
```

`encode()` 函数可以将 Unicode 表示的 `str` **编码** 为对应的 `bytes`,反之则使用 `decode()`.

### string_escape 和 unicode_escape
