#!/usr/bin/python3.6

import csv
from bs4 import BeautifulSoup
import requests
from collections import namedtuple

headers = {'User-Agent' : 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'}
r = requests.get('http://seputu.com' , headers = headers)

soup = BeautifulSoup(r.text , 'lxml')

mulu = soup.find_all(class_ = 'mulu')    # find the mulu
setp  = []
for m in mulu:
    h2 = m.find(name = 'h2')
    if h2 != None:
        h2_title = h2.string
        for a in m.find(class_ = 'box').find_all(name = 'a'):
            a_href = a['href']
            a_title = a['title']
            content = (h2_title , a_title , a_href)
            setp.append(content)
headers = ['title','real_title','href']

with open('daomubiji.csv' , 'w') as f:
    f_csv = csv.writer(f)
    f_csv.writerow(headers)
    f_csv.writerows(setp)
    print("CSV OK!")


