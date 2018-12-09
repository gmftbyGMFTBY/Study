import sys
def test1():
    for line in sys.stdin:
        print(line,end = '')   #Because the stdin can automatic add the character '\n',so we don't need to print the '\n',But Ctrl+Z can give the EOF to the py to end it
def test2():
    print("Something is writed into the dictionary!",file = open('new_txt.txt','w'))
