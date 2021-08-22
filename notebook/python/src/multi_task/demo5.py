#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo5.py
@Time    : 2020/10/05 15:35:55
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

from multiprocessing import Process,Queue
import os, time, random

def write(q):
    for value in ['A', 'B', 'C']:
        print("Put {} to queue".format(value))
        q.put(value)
        time.sleep(random.random())
    print("pid{} write completed".format(os.getpid()))


def read(q):
    while True:
        if not q.empty():
            value = q.get(True)
            print("Get {} from queue".format(value))
            time.sleep(random.random())
        else:
            break
    print("pid{} read completed".format(os.getpid()))

if __name__ == "__main__":
    q = Queue()
    pw = Process(target=write, args=(q,))
    pr = Process(target=read, args=(q,))
    pw.start()
    pw.join()
    pr.start()
    pr.join()
    print("")
    print("All done")