import re
import fileinput
import sys

pattern = re.compile(r'\[(.+?)\]') #choice the group

scope = {}  #global dict

def replacement(match):
    #print(type(match)) #test the type of the match
    code = match.group(1)
    try:
        return str(eval(code,scope))
    except Exception:
        return exec(code,scope)

def main():
    lines = []
    for i in fileinput.input(sys.argv[1:]):
        if fileinput.isfirstline():
            if lines:    #filter the lines = []
                print(re.sub(pattern,replacement,''.join(lines)))
                lines = []
            print(fileinput.filename()+":")
        lines.append(i)
    print(re.sub(pattern,replacement,''.join(lines)))

def trans_file(a):
    print("Begin to process the templates file!")
    for i in fileinput.input(a[0]):
        i = re.match(pattern,i).group(1)
        exec(i,scope)
    
    for lines in fileinput.input(a[1:]):
        #print(lines,end = '')
        if fileinput.isfirstline():
            print(fileinput.filename(),':')
        print(re.sub(pattern,replacement,''.join(lines)),end = '')      #lines include a '\n'

if __name__ == '__main__':
    #trans_file(sys.argv[1:])
    main()
