#!/usr/bin/python3.6
# 本联系用来抓取盗墓笔记官网的标题，章节，章节名称，链接的数据,静态网页抓取的联系
# 生成JSON , CSV格式数据并保存
# http://seputu.com/

import json
from bs4 import BeautifulSoup
import requests
user_agent = 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
headers = {'User-Agent' : user_agent}
r = requests.get('http://seputu.com' , headers = headers)

soup = BeautifulSoup(r.text , 'lxml')

content = []

for mulu in soup.find_all(class_ = 'mulu'):
    h2 = mulu.find(name = 'h2')
    if h2 != None:
        h2_title = h2.string    # get the title
        p = []
        for a in mulu.find(class_ = 'box').find_all(name = 'a'):
            href = a.get('href')    # get the href
            box_title = a.get('title')    # get the small title
            p.append({'href' : href , 'box_title':box_title})
        content.append({'title':h2_title , 'content' : p})

with open('daomubiji.json' , 'w') as f:
    json.dump(content , f , indent = 4 , ensure_ascii = False)
    print("Save JSON OK!")

