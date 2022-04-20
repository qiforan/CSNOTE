# JS Overview

## 概述

将 `JavaScript` 插入 `HTML` 的主要方法是使用 `<script>` 元素。

`<script>` 元素属性:

* `src`: 可选。表示包含要执行的代码的外部文件。

* `type`:可选。按照惯例，这个值始终都是 `text/javascript`, 因此不需要指定。

* `async`: 可选。表示应该立即开始下载脚本，但不能阻止其他页面动作。

* `defer`: 可选。表示脚本可以延迟到文档完全被解析和显示之后再执行。只对外部脚本文件有效。

使用 `<script>` 的方式有两种:直接在网页中嵌入 JavaScript 代码，以及通过它在网页中包含外部 JavaScript 文件。

要嵌入行内 JavaScript 代码，直接把代码放在 `<script>` 元素中就行。

引入外部文件中的 JavaScript，就必须使用 `src` 属性。这个属性的值是一个 `URL`，指向包含 JavaScript 代码的文件。浏览器在解析这个资源时，会向 src 属性指定的路径发送一个 GET 请求，以取得相应资源。

注意：使用 `src` 属性就不能使用 `<script>` 元素中的 JavaScript 代码了，否则后者会被忽略掉。

过去，所有 `<script>` 元素都被放在页面的 `<head>` 标签内，现代 Web 应用程序通常 将所有 JavaScript 引用放在 `<body>` 元素中的页面内容后面。

除了 `<script>` 元素加载 JavaScript 代码外，还可以操作 DOM API 动态加载脚本。默认情况下， 以这种方式创建的 `<script>` 元素是以异步方式加载的，相当于添加了 `async` 属性。

```javascript
let script = document.createElement('script');
script.src = 'gibberish.js';
script.async = false; // 将异步加载改为同步加载
document.head.appendChild(script);
```

## 语言基础

本节内容主要基于 ECMAScript 第 6 版，即 ES6。

### 基本语法

ECMAScript 的语法很大程度上借鉴了 C 语言和其他类 C 语言。

1. 区分大小写。

2. 标识符第一个字符必须是一个字母、下划线(_)或美元符号($)，剩下的其他字符可以是字母、下划线、美元符号或数字。
3. C 语言风格的注释，包括单行注释和块注释。
4. 严格模式，可以使用 `"use strict";` 来开启。
5. 语句以分号结尾，省略分号意味着由解析器确定语句在哪里结尾。

### 变量

* `var` 声明变量。函数作用域，自动提升到全局作用域顶部。
* `let` 声明变量。块作用域，无变量提升。
* `const` 声明变量。与 let 基本相同，声明时必须赋值，不能修改。
* 无关键字声明，全局变量，挂载到 `window` 对象上。

`var` 变量在全局作用域下可以省略 `var` 关键字，变量挂载到 `window` 对象上。

根据作用域链，变量近的会覆盖远的。

最佳实践:

1. 不使用 `var`

2. `const` 优先，`let` 次之

undefined 和 ReferenceError 的区别: TODO

### 数据类型

ECMAScript 有 6 种简单数据类型(也称为原始类型):Undefined、Null、Boolean、Number、 String 和 Symbol。


#### `typeof` 操作符

对一个值使用 `typeof` 操作符会返回下列字符串之一:

* "undefined"表示值未定义;
* "boolean"表示值为布尔值;
* "string"表示值为字符串;
* "number"表示值为数值;
* "object"表示值为对象(而不是函数)或 null; 
* "function"表示值为函数;
* "symbol"表示值为符号。

特殊情况：
1. `typeof null` 返回的是 "object"。这是因为特殊值 `null` 被认为是一个对空对象的引用。
2. `typeof undefined` 返回的是 "undefined"。这是因为特殊值 `undefined` 被认为是一个未定义的值。
3. `typeof 函数` 返回的是 "function"。虽然函数也是对象，但是 `typeof` 要能区分函数和其他对象。

#### `Undefined`

`Undefined` 类型只有一个值，就是特殊值 `undefined`。当声明了变量但没有初始化时，就相当于给变量赋予了 `undefined` 值

特殊情况：
1. 在对未初始化的变量调用 `typeof` 时，返回的结果是"undefined"，但对未声明的变量调用它时， 返回的结果还是"undefined".

#### `Null` 类型

Null 类型同样只有一个值，即特殊值 `null`。逻辑上讲，`null` 值表示一个空对象指针.

在定义 **要保存** 对象值的变量时，建议使用 `null` 来初始化。这样，只要检查 这个变量的值是不是 null 就可以知道这个变量是否在后来被重新赋予了一个对象的引用。

特殊情况：

1. `undefined` 值是由 `null` 值派生而来的，因此 ECMA-262 将它们定义为表面上相等。

```javascript
console.log(null == undefined);  // true
```

#### Boolean 类型

Boolean(布尔值)类型有两个字面值: `true` 和 `false`。 这两个布尔值不同于数值，因此 true 不等于 1，false 不等于 0。

要将一个其他类型的值转换为布尔值，可以调用 `Boolean()` 函数:

* 空字符串转换为 `false`；
* `0`、`-0`、`NaN` 转换为 `false`；
* `null`、`undefined` 转换为 `false`；
* 其他情况为转换为 `true`。

`if` 等流控制语句会自动执行其他类型值到布尔值的转换。

#### Number 类型

Number 类型使用 IEEE 754 格式表示整数和浮点值.

##### 浮点数

要定义浮点值，数值中必须包含小数点，而且小数点后面必须至少有一个数字。

因为存储浮点值使用的内存空间是存储整数值的两倍，所以 ECMAScript 总是想方设法把值转换为整数。因此 `10.0` 和 `10` 都是整数值。

ECMAScript 中科学记数法的格式要求是一个数值(整数或浮点数)后跟一个大写或小写的字母 e，再加上一个要乘的 10 的多少次幂。比如:

```javascript
let floatNum = 3.125e7; // 等于31250000
```

`NaN`，意思是“不是数值”(Not a Number)，用于表示本来要返回数值的操作失败了(而不是抛出错误)。如除数为 0，除法运算符返回的是 NaN。

NaN 有几个独特的属性。

* 任何涉及 NaN 的操作始终返回 NaN.
* NaN 不等于包括 NaN 在内的任何值，判断 NaN 必须使用 `isNaN()` 函数。

#### 数值转换

`Number()` 函数基于如下规则执行转换。

* true 转换为 1，false 转换为 0。
* null，返回 0。
* undefined，返回 NaN。
* 字符串解析为数值，如果无法解析，返回 NaN。空字符串返回 0.
* object 调用 `valueOf()` 方法。

`parseInt()` 函数尽力去解析整数。如果第一个字符不是数值字符、加号或减号，返回 NaN，否则继续解析直到碰到非数值字符或结束。

```javascript
let num1 = parseInt("1234blue");  // 1234, blue 忽略
 let num2 = parseInt("");         // NaN
let num3 = parseInt("0xA");       // 10, 十六进制的 10
let num4 = parseInt(22.5);        // 22
```

如果知道要解析的值是十六进制，那么可以传入 16 作为第二个参数，以便正确解析。

`parseFloat()` 函数的工作方式跟 `parseInt()` 函数类似.

#### 字符串

String(字符串)数据类型表示零或多个 16 位 Unicode 字符序列。字符串可以使用双引号(")、 单引号(')或反引号(`)标示。

ECMAScript 中的字符串是不可变的。

几乎所有值都有 `toString()` 方法，返回当前值的字符串等价物，除了 `null` 和 `undefined`.

`String()` 函数返回相应类型值的字符串。遵循如下规则

* 有 `toString()` 方法的值调用 `toString()` 方法，返回字符串。
* `null` 返回 `"null"`。
* `undefined` 返回 `"undefined"`。

#### 字符串插值

字符串插值通过在 `${}` 中使用一个 JavaScript 表达式实现:

```javascript
var value = 5;
let str = `value is ${value}`;
console.log(str); // value is 5
```

### Symbol 类型

Symbol(符号)是 ECMAScript 6 新增的数据类型。符号实例是 **唯一、不可变** 的。 符号的用途是确保对象属性使用唯一标识符，不会发生属性冲突的危险。

