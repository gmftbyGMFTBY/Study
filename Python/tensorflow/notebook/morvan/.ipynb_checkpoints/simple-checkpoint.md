## tensorflow 

---

### Tensorflow 处理结构

* 张量流图

* 懒惰处理

* 测试代码

  1. 预测 $$y = 0.1 \cdot x + 0.3$$

     * tensorflow中的大部分数据都是`np.float32`类型 (np模式是float64)
     * tf.zero -> tf.zeros

     ```python
     #!/usr/bin/python3.5

     '''
     predict y = 0.1 * x + 0.3
     '''

     import tensorflow as tf
     import numpy as np

     # create data in x
     x_data = np.random.rand(100).astype(np.float32)
     y_data = x_data * 0.1 + 0.3

     # ---------- tensorflow --------- #

     Weights = tf.Variable(tf.random_uniform([1], -1.0, 1.0))    # 定义变量,使用随机数生成参数
     print(Weights)
     biases = tf.Variable(tf.zeros([1]))
     print(biases)

     y = Weights * x_data + biases

     loss = tf.reduce_mean(tf.square(y - y_data))    # 误差，修正误差
     optimizer = tf.train.GradientDescentOptimizer(0.5)    # 使用梯度下降修正方式，0.5是学习效率
     train = optimizer.minimize(loss)    # 使用优化器修正误差

     init = tf.initialize_all_variables()    # 初始化变量

     # ---------- tensorflow ---------- #

     sess = tf.Session()    # 开启回话
     sess.run(init)         # 开启运行,开始运行init

     for i in range(201):
         sess.run(train)
         if i % 20 == 0 :
             print(i, sess.run(Weights), sess.run(biases))


     ```

     ​

---

