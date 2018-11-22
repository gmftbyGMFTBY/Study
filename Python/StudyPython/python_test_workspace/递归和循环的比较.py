from time import *
fibs = [0,1]
fib = fibs[:]
def loop(x):
    t1 = clock()
    for i in range(x):
        fibs.append(fibs[-1] + fibs[-2])
    return clock() - t1

def no_loop(x):
    t1 = clock()
    def cal(x):
        if x == 0: return
        else:
            fib.append(fib[-1] + fib[-2])
            cal(x-1)
            return
    cal(x)
    return clock() - t1

count = int(input("The count of the input:"))
print("循环的时耗:%f" % loop(count))
print("循环的结果:",fibs)

print("递归的时耗:%f" % no_loop(count))
print("递归的结果:",fib)
