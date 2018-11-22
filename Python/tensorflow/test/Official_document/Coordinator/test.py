#!/usr/bin/python3

import tensorflow as tf
import threading
import time

def loop(coord, id):
    t = 0
    while not coord.should_stop():
        print(id)
        time.sleep(1)
        t += 1
        if (t >= 2 and id == 1):
            coord.request_stop()

coord = tf.train.Coordinator()

# create 10 thread, and only id = 1 thread can stop the coordinate
threads = [threading.Thread(target = loop, args = (coord, i)) for i in  range(10)]

for i in threads:
    i.start()

coord.join(threads)

