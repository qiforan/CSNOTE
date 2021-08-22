# 位操作

- 获取低位1

```c
#define lowbit(x) (x & -x)
```

- 去除低位1

```c
#define rm_lowbit(x) (x & (x-1))
```

- 设置某位为1

```c
#define setbit(x,i) (x | (1 << i))
```

示例：将大写字母转为小写字母。

- 设置某位为0

```c
#define clrbit(x,i) (x & ~(1 << i)) 
```

示例：将小写字母转为大写字母。

## 获取二进制中 1 的个数

- 循环移位法

- 循环位操作法（循环次数就是二进制中1的个数）

- 查表法(不推荐)

```cpp
int BitCount7(unsigned int n)
{ 
    unsigned int table[256] = 
    { 
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 
    }; 

    return table[n &0xff] +
        table[(n >>8) &0xff] +
        table[(n >>16) &0xff] +
        table[(n >>24) &0xff] ;
}
```

- 分治算法

```cpp
int BitCount4(unsigned int n) 
{ 
    n = (n &0x55555555) + ((n >>1) &0x55555555) ; 
    n = (n &0x33333333) + ((n >>2) &0x33333333) ; 
    n = (n &0x0f0f0f0f) + ((n >>4) &0x0f0f0f0f) ; 
    n = (n &0x00ff00ff) + ((n >>8) &0x00ff00ff) ; 
    n = (n &0x0000ffff) + ((n >>16) &0x0000ffff) ; 

    return n ; 
}
```

- MIT HAKMEM 法

```cpp
int BitCount5(unsigned int n)
{
    unsigned int tmp = n - ((n >>1) &033333333333) - ((n >>2) &011111111111);
    return ((tmp + (tmp >>3)) &030707070707) %63;
}
```

说明：支持 64 位以下的整型。
原理：将 6 个比特分为一组，计算每组中 1 的个数，然后对 $2^6-1=63$ 取模。

- [位域](https://en.wikipedia.org/wiki/Bit_field)法

```cpp
struct _byte 
{ 
    unsigned a:1; 
    unsigned b:1; 
    unsigned c:1; 
    unsigned d:1; 
    unsigned e:1; 
    unsigned f:1; 
    unsigned g:1; 
    unsigned h:1; 
}; 

long get_bit_count( unsigned char b ) 
{
    struct _byte *by = (struct _byte*)&b; 
    return (by->a+by->b+by->c+by->d+by->e+by->f+by->g+by->h); 
}
```

- 函数法

```cpp
// built in function of GCC
int  __builtin_popcount(unsigned int)
```
