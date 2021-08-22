#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo3.py
@Time    : 2020/10/05 15:02:57
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

from threading import Thread
import time

def func(num,c=None):
    print(num,c)

if __name__ == "__main__":
    Thread(target=func, args=(1,), kwargs={"c":"c"}).start()