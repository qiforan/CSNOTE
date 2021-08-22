# cis 194 note & homework

## 1. 基础

`=` 表示把右侧的表达式绑定到左侧的名称上。

函数分为普通函数和中缀函数，普通函数调用的优先级最高，高于中缀函数。


一个 List 由方括号括起，其中的元素用逗号分隔开来。

`:` 运算子可以连接一个元素到一个 List 或者字符串之中，而 `++` 运算子则是连接两个 List。

```shell script
Prelude> :t (:)
(:) :: a -> [a] -> [a]
Prelude> :t (++)
(++) :: [a] -> [a] -> [a]
```

### 1.1. List 常见函数

* `length` 返回一个 List 的长度
* `null` 检查一个 List 是否为空
* `reverse` 将一个 List 反转
* `take` 返回一个 List 的前几个元素
* `maximum` 返回一个 List 中最大的那个元素。 
* `minimun` 返回最小的。
* `sum` 返回一个 List 中所有元素的和。
* `elem` 判断一个元素是否在包含于一个 List
* `take` 从 List 取前几个元素 
* `repeat` 接受一个参数，生成该值的无限 List 
* `replicate` 生成相同值的有限 List


### 1.3. List Comprehension


类型参数 值构造子

在声明数据类型时，等号 = 左端的那个是类型构造子，右端的 (中间可能有 | 分隔) 都是值构造子。

类型构造子接受其他类型作为他的参数，来构造出一个具体类型。