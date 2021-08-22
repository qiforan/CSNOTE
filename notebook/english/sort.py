#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : sort.py
@Time    : 2020/11/22 15:53:59
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

file = open("english/words.md", "r")

content = []

while True:
    text = file.readline()
    if len(text) > 1:
        content.append(text)
    if not text:
        break
    
content = [line+"\n" for line in content]
head = content[0]
content = content[1:]
content = sorted(content)
content.insert(0, head)

file.close()

file = open("english/words_sorted.md","w")
file.writelines(content)
file.close()


