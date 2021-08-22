#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo3.py
@Time    : 2020/10/05 19:59:49
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : 提取区号
'''

import re

def func(string):
    result = re.match("([^-]*)-(\d+)$",string)
    if result:
        print(result.group(1),result.group(2))
    else:
        print("No match")

if __name__ == "__main__":
    func("010-12343556")

