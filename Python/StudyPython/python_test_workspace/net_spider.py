from http.client import *

con = HTTPConnection("www.cnblogs.com")
con.request("GET","/vamei")
res = con.getresponse()
content = res.read()
print(type(content))
content = content.decode("utf-8")
print(type(content))
ans = content.split("\r\n")
print(len(ans))
for i in range(10):
    print(ans[i])
