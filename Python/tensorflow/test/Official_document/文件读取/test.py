#!/usr/bin/python3

import tensorflow as tf

with tf.Session() as sess:
    filename = ['1.jpg', '2.jpg', '3.jpg']
    filename_queue = tf.train.string_input_producer(filename, shuffle=True, num_epochs=3)
    reader = tf.WholeFileReader()
    key, value = reader.read(filename_queue)
    sess.run(tf.local_variables_initializer())
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
    sess.close()

