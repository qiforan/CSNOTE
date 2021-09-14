#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : ecard.py
@Time    : 2020/11/22 17:00:59
@Author  : Chenghou Wang
@Contact : xhchengx@gmail.com
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : 统计 ecard 消费
'''


import requests
import re
import os
import time
import math
import random
from xml.etree import ElementTree
from dateutil.rrule import rrule, MONTHLY
from datetime import datetime
import csv

from requests.models import Response


def write_csv(month_str, content):
    with open("data/"+month_str+".csv", "w+") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(content)


def is_csv_exists(month_str):
    return os.path.exists("data/"+month_str+".csv")


def get_month_str_list(start_year, start_month, end_year, end_month):
    start = datetime(start_year, start_month, 1)
    end = datetime(end_year, end_month, 1)
    return ["{}-{:02d}".format(d.year, d.month) for d in rrule(MONTHLY, dtstart=start, until=end)]


def get_month_detail(month_str):
    url = "https://ecard.ustc.edu.cn/paylist/ajax_get_paylist"
    headers = {
        "authority": "ecard.ustc.edu.cn",
        "method": "POST",
        "path": "/paylist/ajax_get_paylist",
        "scheme": "https",
        "accept": "text/html, */*; q=0.01",
        "accept-encoding": "gzip, deflate, br",
        "accept-language": "en,zh-CN;q=0.9,zh;q=0.8",
        "content-length": "12",
        "content-type": "application/x-www-form-urlencoded; charset=UTF-8",
        "cookie": "PHPSESSID=ST-6dc23110ed214370b96a953e4a7d441e; XSRF-TOKEN=eyJpdiI6IjdmNlg4NlU0ZXI5ODJORjJBbGhTZGc9PSIsInZhbHVlIjoibVc5Skt5eU1tc3ZicFlMZjFhTFo2U1BaTXREOWV2N3pHXC9uTVYrTFVKaXNEMktzWWVXZVFrb1diSENSXC9GUzcxYnA3eFhsaTNQWkVvVTM5MnVcL1ZVeHc9PSIsIm1hYyI6ImE3M2IwM2U1NDlmN2ZjODE5MTM5ODk5MDMwYmFmNjIyNTZkZTRlODRkZjEwMzE2NjgyYjRkY2I3YTIwZDEyNTUifQ%3D%3D; laravel_session=eyJpdiI6IkprOUxibm9icDBEeEVnNUYxeGUzdmc9PSIsInZhbHVlIjoiTDR3a1VQdTRjUTZNa2Y5VVJOUG9rQnNtSFpMTVpCcWZreldBV0ZlbmFXbmcyM2I5NGVhOGVhOUFmZlVHRXAwdDJoYk1WOHdrU2F3Rk5QZlwvRTBwTndRPT0iLCJtYWMiOiI3YTFmYWY0YjQ4MmFiZDBlYmNjMDQ2MDE2NGZjMTk4ODRjZTQ5NWFhNzYxNjgyOGY3NGI0NDI0ZDM1NmQ1YmY0In0%3D",
        "origin": "https://ecard.ustc.edu.cn",
        "referer": "https://ecard.ustc.edu.cn/paylist/ajax_get_paylist?page=2",
        "sec-fetch-dest": "empty",
        "sec-fetch-mode": "cors",
        "sec-fetch-site": "same-origin",
        "user-agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.75 Safari/537.36",
        "x-csrf-token": "gT7d0tYLrU7WTUhXhfmJmYhNdlf1E7ozziviPuyn",
        "x-requested-with": "XMLHttpRequest"
    }
    forms = {
        "page": "1",
        "date": "2020-10" 
    }
    response = requests.post(url, headers=headers, data=forms)
    print(response.text)
    head_pattern = r'<th>(.*?)</th>'
    body_pattern = r'<td>(.*?)</td>'
    info_pattern = r'<li>共(.*?)条记录</li>'
    head_list = re.findall(head_pattern, response.text, re.S | re.M)
    body_list = re.findall(body_pattern, response.text, re.S | re.M)
    if len(body_list) == 0:
        print("{} 没有记录".format(month_str))
        return
    content = [head_list]
    info = re.findall(info_pattern, response.text, re.S | re.M)[0]
    column_length = len(head_list)
    row_length = len(body_list) // column_length
    page_length = int(math.ceil(int(info)/row_length))
    print("{}有{}条记录，共{}页".format(month_str, info, page_length))
    for page in range(page_length, 0, -1):
        forms = {
            "page": page,
            "date": month_str
        }
        time.sleep(random.random())
        response = requests.post(url, headers=headers, data=forms)
        print("正在读取第{}页".format(page_length+1-page))
        body_list = re.findall(body_pattern, response.text, re.S | re.M)
        page_content = []
        for i in range(len(body_list)//column_length):
            page_content.append([])
            for j in range(column_length):
                page_content[-1].append(body_list[i*column_length+j])
        page_content.reverse()
        content = content + page_content
    write_csv(month_str, content)


def get_data(start="2019-09", end=None, page=None, renew=False):

    date = None
    start_date_list = [int(x) for x in start.split("-")]
    end_date_list = time.localtime(time.time())[:2]
    if end:
        end_date_list = [int(x) for x in end.split("-")]
    month_list = get_month_str_list(
        start_date_list[0], start_date_list[1], end_date_list[0], end_date_list[1])
    print(month_list)
    for month in month_list:
        if renew == False and is_csv_exists(month):
            continue
        month_content = get_month_detail(month)


if __name__ == "__main__":
    get_data()
