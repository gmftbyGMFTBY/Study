def flattern(nested):
    '''该生成器用来生成展开列表的元素,递归生成器'''
    try:
        if isinstance(nested,str):yield nested
        else:
            for some in nested:
                for i in flattern(some):
                    print("test!")
                    yield i
    except TypeError:
        print("|||||")
        yield nested

for i in flattern([[1,2,3],4,5,[[6,7],8,9],10]):
    print(i)
