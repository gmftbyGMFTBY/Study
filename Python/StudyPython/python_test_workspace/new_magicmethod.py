class Counterlist(list):
    def __init__(self,*args):
        super().__init__(*args)
        self.counter = 0
    def __getitem__(self,key):
        self.counter += 1
        return super().__getitem__(key)

p = Counterlist((1,343,6,5,85,642,56,44,3457,43,46,43))
p.sort()
print(p)
print(p[2] + p[4])
print(p.counter) 

