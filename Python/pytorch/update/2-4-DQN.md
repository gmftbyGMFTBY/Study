## DQN with PyTorch

---

1. 导入

   ```python
   import gym
   import math
   import random
   import numpy as np
   import matplotlib
   import matplotlib.pyplot as plt
   from collections import namedtuple
   from itertools import count
   from copy import deepcopy
   from PIL import Image

   import torch
   import torch.nn as nn
   import torch.optim as optim
   import torch.nn.functional as F
   from torch.autograd import Variable
   import torchvision.transforms as T


   env = gym.make('CartPole-v0').unwrapped

   # 设置 matplotlib
   is_ipython = 'inline' in matplotlib.get_backend()
   if is_ipython:
       from IPython import display

   plt.ion()

   # 如果要使用 gpu 的话
   use_cuda = torch.cuda.is_available()
   FloatTensor = torch.cuda.FloatTensor if use_cuda else torch.FloatTensor
   LongTensor = torch.cuda.LongTensor if use_cuda else torch.LongTensor
   ByteTensor = torch.cuda.ByteTensor if use_cuda else torch.ByteTensor
   Tensor = FloatTensor
   ```

2. 重播记忆

   我们将使用体验重播记忆来训练我们的DQN. 它存储了代理观察到的变化过程, 允许我们之后能够 重复使用这些数据. 通过对重播记忆随机取样, 建立了批处理的变化过程将会被解耦合. 这一机制 也被证明能够大幅度地提高和优化 DNQ 训练步骤的稳定性

   * Transition: namedtuple 表示环境的单次变化
   * ReplayMemory: 有限大小的循环缓冲区，保存最近的观察到的过程，可以使用 `.sample` 方法抽取 minibatch 数据实现 iid

   ```python
   Transition = namedtuple('Transition',
                           ('state', 'action', 'next_state', 'reward'))


   class ReplayMemory(object):

       def __init__(self, capacity):
           self.capacity = capacity
           self.memory = []
           self.position = 0

       def push(self, *args):
           """Saves a transition."""
           if len(self.memory) < self.capacity:
               self.memory.append(None)
           self.memory[self.position] = Transition(*args)
           self.position = (self.position + 1) % self.capacity

       def sample(self, batch_size):
           return random.sample(self.memory, batch_size)

       def __len__(self):
           return len(self.memory)
   ```

3. DQN

   ​