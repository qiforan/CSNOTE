#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo4.py
@Time    : 2020/10/05 15:25:29
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

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