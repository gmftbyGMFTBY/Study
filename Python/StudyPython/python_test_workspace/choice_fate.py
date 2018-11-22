import fileinput
import sys
import random

print(random.choice(list(fileinput.input(sys.argv[1:]))),end = '')
