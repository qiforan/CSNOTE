#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo8.py
@Time    : 2020/10/05 17:10:48
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

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