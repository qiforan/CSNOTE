#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo4.py
@Time    : 2020/10/05 20:03:38
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : 匹配不是以4和7结尾的手机号(11位)
'''

import re

def func(string):
    result = re.match("1[0-9]{9}(?![47])[\d]$", string)
    if result:
        print(result.group())
    else:
        print("No match")

if __name__ == "__main__":
    func("18800007774")

