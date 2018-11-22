from time import *
from http.client import *

def decorator_time(old_function):
    def new_function(string_url):
        t1 = clock()
        old_function(string_url)
        t2 = clock()
        print("Time:",t2-t1)
    return new_function

@decorator_time
def get_http(pos):
    con = HTTPConnection(pos)
    con.request("GET","/")
    res = con.getresponse()
    print(res.status,res.reason)
    content = res.read()
    #print(content)
    k = str(content).split("\r\n")
    print(len(k))

get_http("www.baidu.com")

