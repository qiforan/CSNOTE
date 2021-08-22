#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo9.py
@Time    : 2020/10/05 17:49:50
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

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