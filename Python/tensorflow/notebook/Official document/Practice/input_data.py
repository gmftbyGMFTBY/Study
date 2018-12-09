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

def read_data(batch_size):
    dataset = read_data_sets('./MNIST_data', one_hot=True)
    
    # show the train dataset - 55000
    # print(dataset.train.images, dataset.train.images.shape)
    # print(dataset.train.labels, dataset.train.labels.shape)
    
    # show the validation dataset - 5000
    # print(dataset.validation.images, dataset.validation.images.shape)
    # print(dataset.validation.labels, dataset.validation.labels.shape)
        
    # show the test dataset - 10000
    # print(dataset.test.images, dataset.test.images.shape)
    # print(dataset.test.labels, dataset.test.labels.shape)
    
    # next batch for the training
    # once get one batch tuple of the images and the labels
    train_images_feed, train_labels_feed = dataset.train.next_batch(batch_size)
    return train_images_feed, train_labels_feed

def read_test():
    dataset = read_data_sets('./MNIST_data', one_hot=True)
    return dataset.test.images, dataset.test.labels