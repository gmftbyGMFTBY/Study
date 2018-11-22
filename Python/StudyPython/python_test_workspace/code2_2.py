import re
url = input("Please input your URL:")
pattern = "http://www.(.+)\.com"
an = re.findall(pattern,url)
print(an.group(1))

