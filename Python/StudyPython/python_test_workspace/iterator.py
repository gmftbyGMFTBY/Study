class fibs():
    def __init__(self):
        self.a = 0
        self.b = 1
    def __next__(self):
        self.a,self.b = self.b,self.a + self.b
        if self.a > 1000:raise StopIteration
        return self.a
    def __iter__(self):
        print("I am iterator!")
        return self

p = fibs()
#k = p.__iter__()
for i in p:
    print(i)
print(list(fibs()))

