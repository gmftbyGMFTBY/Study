#!/usr/bin/python

'''Linear Regression method test in PyTorch

y = wx + b + e    # e is the loss for the Linear Regression method
=> Get the Loss function
loss = \sum_{i}^N\frac{1}{2}(y_i-(wx_i+b))^2
'''

import torch
from matplotlib import pyplot as plt
from IPython import display
from torch import optim
from torch.autograd import Variable
import torch.nn as nn

torch.manual_seed(1000)

def get_fake_data(batch_size=8):
    '''produce the random data: y = x * 2 + 3, add the noise'''
    x = torch.rand(batch_size, 1) * 20    # (8, 1)
    y = x * 2 + (1 + torch.randn(batch_size, 1)) * 3    # add the noise to the result
    return x, y

w = Variable(torch.rand(1, 1), requires_grad=True)
b = Variable(torch.randn(1, 1), requires_grad=True)
lr = 0.05
optimizer = optim.SGD([w, b], lr = lr)
criterion = nn.MSELoss()

for ii in range(20000):
    x, y = get_fake_data()
    y_pred = x.mm(w) + b.expand_as(y)
    loss = criterion(y_pred, y)

    optimizer.zero_grad()
    loss.backward()
    nn.utils.clip_grad_norm([w, b], 0.2)    # prevent the grad explod
    optimizer.step()

    if ii % 1000 == 0:
        print(w.squeeze()[0], b.squeeze()[0])

if __name__ == "__main__":
    pass
