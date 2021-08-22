#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    : math_fomula_transform.py
@Time    : 2020/09/15 14:40:30
@Author  : Chenghou Wang
@Contact : wch162@mail.ustc.edu.cn
@Version : 0.1
@License : Apache License Version 2.0, January 2004
@Desc    : transform the math formula that cant be displayed in github to images
@Usage   : python3 math_fomula_transform.py [file-path]
'''


import re
import os
import argparse
from urllib.parse import quote

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("filepath", help="the markdown file")
    filepath = parser.parse_args().filepath
    text = open(filepath, encoding="utf-8").read()

    parts = text.split("$$")

    for i, part in enumerate(parts):
        if i & 1:
            parts[i] = f'![math](https://render.githubusercontent.com/render/math?math={quote(part.strip())})'

    text_out = "\n\n".join(parts)

    lines = text_out.split('\n')
    for lid, line in enumerate(lines):
        parts = re.split(r"\$(.*?)\$", line)
        for i, part in enumerate(parts):
            if i & 1:
                parts[
                    i] = f'![math](https://render.githubusercontent.com/render/math?math={quote(part.strip())})'
        lines[lid] = ' '.join(parts)
    text_out = "\n".join(lines)

    file_path, file_name = os.path.split(filepath)
    file_name_with_ext, ext = os.path.splitext(file_name)
    with open(os.path.join(file_path, file_name + "_github"+ext), "w", encoding='utf-8') as f:
        f.write(text_out)
