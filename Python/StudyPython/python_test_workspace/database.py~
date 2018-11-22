'''Try to input the only one argv into the py'''
import sys,shelve

def store(myfile):
    person = {}
    numbers = input("Please input your numbers: ")
    person['name'] = input("Please input your name: ")
    person['age'] = input("Please input your age: ")
    person['phone'] = input("Please inputyour phone-number: ")
    myfile[numbers] = person
def lookup(myfile):
    numbers = input("Please input the numbers: ")
    details = input("What would you want to know: ")
    try:
         print(myfile[numbers][details])
    except Exception as e:
         print("Can not find the information!")

def print_help():
    dic = {}
    dic["store"] = 'store the person information into the file!'
    dic['lookup'] = 'search the person in the file!'
    dic['?'] = 'print the help information!'
    dic['quit'] = 'quit the programm'
    for i,j in dic.items():
        print(i + ':\n' + j)

def main():
    myfile = shelve.open(sys.argv[1])
    try:
        while True:
            cmd = input("Please input your command : ").strip().lower()
            if cmd == 'store':
                store(myfile)
            elif cmd == 'lookup':
                lookup(myfile)
            elif cmd == '?':
                print_help()
            elif cmd == 'quit':
                print("Thank you!")
                sys.exit()
            else:print("Can not find the command!")
    except Exception as e:
        print(e)
    finally:
        myfile.close()

if __name__ == '__main__':
    main()
