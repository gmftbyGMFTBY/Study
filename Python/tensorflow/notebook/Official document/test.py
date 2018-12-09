import tensorflow as tf
'''
# 保存变量
v1 = tf.Variable(1, name="v1")
v2 = tf.Variable(2, name='v2')

init = tf.global_variables_initializer()

# 指定要保存的变量字典
saver = tf.train.Saver({'v3': v1, 'v4':v2})

with tf.Session() as sess:
    sess.run(init)
    save_path = saver.save(sess, './tmp/test.ckpt')
    print('Model save into:', save_path)
    print(sess.run([v1, v2]))

'''
# 加载变量
with tf.Session() as sess:
    v5 = tf.Variable(30, name='v3')
    v6 = tf.Variable(40, name='v4')
    init = tf.global_variables_initializer()
    sess.run(init)
    print(sess.run([v5, v6]))
    saver = tf.train.Saver()
    saver.restore(sess, './tmp/test.ckpt')
    print(sess.run([v5, v6]))
