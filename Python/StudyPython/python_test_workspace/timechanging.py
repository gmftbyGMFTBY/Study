import time
import sys
import collections

def time_change(a):
    while True:
        print(''.join(a)+'\r',end = '')
        a.rotate(1)
        time.sleep(0.1)

if __name__ == '__main__':
    time_change(collections.deque('>---------'))
