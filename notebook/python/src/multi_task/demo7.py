#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : demo7.py
@Time    : 2020/10/05 16:48:43
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : None
'''

class MyIterator(object):
    def __init__(self, mylist):
        self.mylist = mylist
        self.current = 0
    
    def __next__(self):
        if self.current < len(self.mylist.items):
            item = self.mylist.items[self.current]
            self.current += 1
            return item
        else:
            raise StopIteration
    
    def __iter__(self):
        return self

class MyList(object):
    def __init__(self):
        self.items = []
    
    def add(self, val):
        self.items.append(val)

    def __iter__(self):
        my_iterator = MyIterator(self)
        return my_iterator

if __name__ == "__main__":
    my_list = MyList()
    for i in range(5):
        my_list.add(i)
    for i in my_list:
        print(i)
    



