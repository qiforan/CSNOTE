#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo6.py
@Time    : 2020/10/05 15:51:54
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

from multiprocessing import Pool
import os, time, random

def func(msg):
    t_start = time.time()
    print("{} start, pid {}".format(msg, os.getpid()))
    time.sleep(random.random()*2)
    print(msg, " completd in {:.2f}s".format(time.time() - t_start))

if __name__ == "__main__":
    po = Pool(3)
    for i in range(10):
        po.apply_async(func,(i,))
    print('----start ----')
    po.close()
    po.join()
    print('----end ----')
