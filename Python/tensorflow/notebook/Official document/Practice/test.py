# ---------- 数据输入 ---------- #
# Copyright 2015 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================

"""Functions for downloading and reading MNIST data."""
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import gzip
import os
import tempfile

import numpy
from six.moves import urllib
from six.moves import xrange  # pylint: disable=redefined-builtin
import tensorflow as tf
from tensorflow.contrib.learn.python.learn.datasets.mnist import read_data_sets

dataset = read_data_sets('./MNIST_data', one_hot=True)

# --------- 定义输入占位节点 ---------- #
x = tf.placeholder("float", shape=[None, 784])
y_ = tf.placeholder("float", shape=[None, 10])

# --------- 定义参数(权重， 偏置) ---------- #
def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)    # 保证正态分布的区间维持在 -0.2 ~ 0.2 之间
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

# 卷积层和池化层
# 池化层 : 2 * 2 Max Pooling
# 卷积层函数 : tf.nn.conv2d
def conv2d(x, W):
    # x是输入的tensor,四个维度[batch, height, width, channels]
    # W是卷积核tensor,四个维度[height, width, in_channels, out_channels],out_channels可以理解成是过滤器的个数
    # strides是对输入四个维度的滑动窗口的步长
    # padding='SAME'表示卷积层之后输出和输入的规模不变
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
    # x是输入的四维tensor
    # ksize代表窗口的大小
    # strides是步长
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

# ---------- 第一卷积层 ---------- #
# 第一卷积层的权重，初始化卷积核和偏置参数(32个卷积核，每个卷积核的大小是5 * 5, 因为是灰度图像，没有颜色通道，所以in_channels是1)
# 第一层的卷积层的偏置有32个（针对32个卷积核）
W_conv1 = weight_variable([5, 5, 1, 32])
b_conv1 = bias_variable([32])

# 重组输入的图片的tensor规模，28,28是图像的高和宽，1是通道数(灰度图片只有一个通道),-1自调整batch的大小
x_image = tf.reshape(x, [-1, 28, 28, 1])

# 线性整流和池化
# 28 - 1 + 1 = 28 -> 28 * 28
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
# ( 28 - 2 ) / 2 + 1 = 14 -> 14 * 14
h_pool1 = max_pool_2x2(h_conv1)

# ----------- 第二卷积层 ---------- #
# 特征数目扩展到64,64个卷积核
# h_pool1 作为输入
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])

# 14 - 1 + 1 = 14 -> 14 * 14
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
# ( 14 - 2 ) / 2 + 1 = 7 -> 7 * 7
h_pool2 = max_pool_2x2(h_conv2)

# ---------- 全连接层 ---------- #
# 此时的图像的大小是 7 * 7 * 64 (7 * 7 大小，６４个特征)
# 3136 -> 1024 的一个全连接层
W_fc1 = weight_variable([7 * 7 * 64, 1024])
b_fc1 = bias_variable([1024])

# 展开成一维向量 (1, 7 * 7 * 64)
h_pool2_flat = tf.reshape(h_pool2, [-1, 7 * 7 * 64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)

# ---------- 避免过拟合 dropout ---------- #
# 神经元被drop的概率
keep_prob = tf.placeholder("float")
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

# --------- Softmax 输出层 --------- #
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])

y_conv=tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

# --------- 评估和训练 ---------- #
# 定义交叉熵
cross_entropy = -tf.reduce_sum(y_ * tf.log(y_conv))
# 使用ADAM梯度最速下降步长是 1e-4 优化损失函数交叉熵
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
# 正确率计算
correct_prediction = tf.equal(tf.argmax(y_conv,1), tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

sess = tf.Session()
sess.run(tf.global_variables_initializer())
for i in range(5000):
    # 随机梯度下降
    batch = dataset.train.next_batch(50)
    # 每100次执行一次计算准确率
    if i % 100 == 0:
        train_accuracy = sess.run(accuracy, feed_dict={x:batch[0], y_: batch[1], keep_prob: 1.0})
        print("step %d, training accuracy %g" % (i, train_accuracy))
    sess.run(train_step, feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})

# 评估
# 容易出现bad_alloc的情况，内存不够用的内存分配错误
test_batch = dataset.test.next_batch(1000)
print("test accuracy %g" % sess.run(accuracy, feed_dict={x: test_batch[0], y_: test_batch[1], keep_prob: 1.0}))
sess.close()
