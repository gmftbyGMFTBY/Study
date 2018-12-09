class fibs():
    def __init__(self):
        self.a,self.b = 0,1
    def __next__(self):
        self.a,self.b = self.b,self.a+self.b
        return self.a
    def __iter__(self):
        print("返回一个迭代器")
        return self

p = fibs()
print(p.__next__())
print(p.__next__())
print(p.__next__())
w = p.__iter__()
print(p,w)
for i in w:
    if i > 1000:break
    else: print(i)
