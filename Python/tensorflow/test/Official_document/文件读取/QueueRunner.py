#!/usr/bin/python3

import tensorflow as tf

'''
with tf.Session() as sess:
    filename = ['1.jpg', '2.jpg', '3.jpg']
    filename_queue = tf.train.string_input_producer(filename, shuffle=True, num_epochs=3)
    reader = tf.WholeFileReader()
    key, value = reader.read(filename_queue)
    sess.run(tf.local_variables_initializer())   # 因为string_input_producer内部创建了一个epoch比那辆计数器，归入到tf.GraphKeys.LOCAL_VARIABLES集合中，必须使用local_variables_initlizer()
    sess.run(tf.global_variables_initializer())
    coord = tf.train.Coordinator()
    threads = tf.train.start_queue_runners(sess=sess, coord = coord)

    # print two queue information
    queue_runners = tf.get_collection(tf.GraphKeys.QUEUE_RUNNERS)
    for qr in queue_runners:
        print('-' * 20)
        print(type(qr.queue))
        print(qr.queue.name)
        for operation in qr.enqueue_ops:
            print(type(operation))
            print(operation.name)

    i = 0
    try:
        while not coord.should_stop():
            image = sess.run(value)
            with open('test/test_%d' % i, 'wb') as f:
                print('ready to write the file test%d' % i)
                f.write(image)
            i += 1
    except tf.errors.OutOfRangeError:
        print('The queue is done')
    finally:
        coord.request_stop()

    print('Begin the main thread ...')
    coord.join(threads)
'''

with tf.Session() as sess:
    coord = tf.train.Coordinator()
    filename = ['1.jpg', '2.jpg', '3.jpg']
    filename_queue = tf.train.string_input_producer(filename, shuffle=False, num_epochs=3)
    reader = tf.WholeFileReader()
    key, value = reader.read(filename_queue)
    sess.run(tf.local_variables_initializer())
    queue = tf.FIFOQueue(10, dtypes='string')
    en_queue = queue.enqueue(value)
    qr = tf.train.QueueRunner(queue, enqueue_ops = [en_queue] * 10)
    threads = qr.create_threads(sess, coord = coord, start = True)

    tf.train.start_queue_runners(sess=sess, coord = coord)

    i = 0
    try:
        # 上面的都是读取进程，下面的是执行进程
        while not coord.should_stop():
            image = sess.run(queue.dequeue())
            with open('test/test_%d' % i, 'wb') as f:
                print('ready to write the file test%d' % i)
                f.write(image)
            i += 1
    except tf.errors.OutOfRangeError:
        print('The queue is done ...')
    finally:
        coord.request_stop()

    coord.join(threads)

