#!/usr/bin/python3.6
# Only save 100 item from the baidubaike

import requests

class URLmanager:
    '''
        This Class define the URL manager and 
        try to create two set for the spider.
    '''
    def __init__(self):
        '''
            Create two set fot the URL manager.
        '''
        self.new_urls = set()
        self.old_urls = set()
    def has_new_url(self):
        '''
            Bool - judge if there are any new url in 
            new_urls set.
        '''
        return self.new_url_size() > 0
    def get_new_url(self):
        '''
            get one url from the new_urls set.
        '''
        new_url = self.new_urls.pop()
        self.old_urls.add(new_url)
        return new_url
    def new_url_size(self):
        return len(self.new_urls)
    def old_url_size(self):
        return len(self.old_urls)
    def add_new_url(self , url):
        '''
            add the correct url into the new_urls.
        '''
        if url is None:return
        if url not in self.new_urls and url not in self.old_urls:
            self.new_urls.add(url)
    def add_new_urls(self , urls):
        '''
            add lot of urls into the new_urls.
            urls must be a sqeuence
        '''
        if len(urls) == 0 or urls is None:return 
        for url in urls:
            self.add_new_url(url)

class HTMLDownloader:
    def download(self , url):
        if url is None:return None
        headers = {'User-Agent':'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'}
        r = requests.get(url , headers = headers)
        if r.status_code == 200:    # Download successfully
            r.encoding = 'utf8'
            return r.text
        else :
            print("Download failed.")
            return None

from bs4 import BeautifulSoup
import lxml
import re
import urllib.parse

class HTMLParser:
    def parser(self , page_url , html_content):
        '''
            parser the data the url from the HTML page.
        '''
        if page_url is None or html_content is None : return 
        soup = BeautifulSoup(html_content , 'lxml')
        new_urls = self._get_new_urls(page_url , soup)
        new_content = self._get_new_content(page_url , soup)
        return new_urls , new_content
    def _get_new_urls(self , page_url , soup):
        new_urls = set()
        for url in soup.find_all(name = 'a' , target = "_blank" , href = re.compile(r'/item/.*')):    #　use the r'' string to regex
            new = url['href']
            new_full_url = urllib.parse.urljoin(page_url , new)
            new_urls.add(new_full_url)
        return new_urls
    def _get_new_content(self , page_url , soup):
        data = {}
        data['url'] = page_url
        data['title'] = soup.find(name = 'dd' , class_ = 'lemmaWgt-lemmaTitle-title').find(name = 'h1').string
        # 永远不要对着None使用is ,而是==
        data['summary'] = soup.find(name = 'div' , class_ = 'lemma-summary').get_text()
        return data

class HTMLOutput:
    def __init__(self):
        self.datas = []
    def store(self , data):
        if data is None : return
        self.datas.append(data)
    def output_html(self):
        with open('/home/lantian/spider_result.html' , 'w' ,encoding = 'utf-8') as f:
            f.write('<html><head><meta charset = "UTF8"/></head>')
            f.write('<body><table>')
            for data in self.datas:
                f.write('<tr>')
                f.write('<td>%s</td>' % data['url'])
                f.write('<td>%s</td>' % data['title'])
                f.write('<td>%s</td>' % data['summary'])
                f.write('</tr>')
            f.write('</table></body></html>')

class Spider:
    def __init__(self):
        self.manager = URLmanager()
        self.downloader = HTMLDownloader()
        self.htmlparser = HTMLParser()
        self.output = HTMLOutput()
        print("4 module has been ready.")
    def run(self, root_url):
        self.manager.add_new_url(root_url)
        while self.manager.old_url_size() < 100 and self.manager.has_new_url():
            try:
                new_url = self.manager.get_new_url()
                html = self.downloader.download(new_url)
                new_urls , new_content = self.htmlparser.parser(new_url , html)
                self.manager.add_new_urls(new_urls)
                self.output.store(new_content)
                print("已经抓取%s链接" % self.manager.old_url_size() , end = '\r')
            except Exception as e:
                print("Something run with the run function.")
                print(e)
        self.output.output_html()

if __name__ == "__main__":
    spider = Spider()
    spider.run('https://baike.baidu.com/item/%E7%BD%91%E7%BB%9C%E7%88%AC%E8%99%AB')
