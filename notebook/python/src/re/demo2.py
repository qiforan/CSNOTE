#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo2.py
@Time    : 2020/10/05 19:44:00
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : 匹配0-99,并测试
'''

import re

counter = 0
for i in range(100):
    if re.match(r"[1-9]\d?$|0$",str(i)):
        counter += 1
print(counter)