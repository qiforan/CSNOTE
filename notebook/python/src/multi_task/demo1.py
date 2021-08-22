#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo1.py
@Time    : 2020/10/05 14:40:45
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

import threading
import time

def func():
    for i in range(100):
        print(i)
        time.sleep(1)

if __name__ == "__main__":
    t = threading.Thread(target=func)
    t.start()