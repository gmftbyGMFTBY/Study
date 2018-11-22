def flattern(nested):
    try:
        for sub in nested:
            for element in flattern(sub):
                #print("回来了",sub,element)
                yield element
                pass
    except TypeError:
        #print("TypeError!")
        yield nested

for i in flattern([[1,2],3]):
    print(i)
