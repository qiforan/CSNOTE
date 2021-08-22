#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo1.py
@Time    : 2020/10/05 18:39:38
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : re的基本使用
'''
import re
# pattern string
result = re.match("123","b123abc123")
if result:
    print(result.group())
else:
    print("No match")