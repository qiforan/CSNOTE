#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo2.py
@Time    : 2020/10/05 14:48:08
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

import threading
import time

class MyThread(threading.Thread):
    def run(self):
        for i in range(3):
            time.sleep(1)
            msg = "{} @ {}".format(self.name, i)
            print(msg)

if __name__ == "__main__":
    for i in range(3):
        MyThread().start()