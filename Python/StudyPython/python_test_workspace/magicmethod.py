def checkindex(key):
    '''检查键是否合法：
    负数 - 不合法 - 建立无穷序列
    非整数不合法'''
    if not isinstance(key,int):raise TypeError
    elif key < 0 :raise IndexError
class unlongseq():
    def __init__(self,start = 0,step = 1):
        self.start = start 
        self.step = step
        self.change = {}
    def __len__(self):
        return 0
    def __getitem__(self,key):
        checkindex(key)
        try:
            return self.change[key]
        except KeyError:
            return self.start + self.step * key
    def __setitem__(self,key,value):
        checkindex(key)      
        self.change[key] = value

p = unlongseq()
print(len(p))
print(p[2])
p[4] = -1
print(p[4])
print(p)
