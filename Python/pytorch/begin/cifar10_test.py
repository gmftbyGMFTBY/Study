#!/usr/bin/python3

# 1. load cidar10
import torch
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import torch.nn.functional as F
import torch.nn as nn
from torch.autograd import Variable
import numpy as np
import torch.optim as optim

# CNN for CIFAR-10

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(3, 6, 5)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)
    
    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(-1, 16 * 5 * 5)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x


# 数据预处理
transform = transforms.Compose(
        [transforms.ToTensor(),
         transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])

# 数据加载
# the data in the special path
trainset = torchvision.datasets.CIFAR10(root='/home/lantian/Downloads/dataset/cifar/', train=True,
        download=True, transform=transform)
trainloader = torch.utils.data.DataLoader(trainset, batch_size=4,
        shuffle=True, num_workers=2)

testset = torchvision.datasets.CIFAR10(root='/home/lantian/Downloads/dataset/cifar/', train=False,
        download=True, transform=transform)
testloader = torch.utils.data.DataLoader(testset, batch_size=4,
        shuffle=False, num_workers=2)

classes = ('plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

# show the `imgs`
def imshow(img):
    img = img / 2 + 0.5
    npimg = img.numpy()
    plt.imshow(np.transpose(npimg, (1, 2, 0)))
    plt.show()        # this line is the nessceary

# dataiter = iter(trainloader)
# images, labels = dataiter.next()

# print(' '.join('%5s' % classes[labels[j]] for j in range(4)))
# imshow(torchvision.utils.make_grid(images))

# NN
net = Net()
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(net.parameters(), lr = 0.001, momentum = 0.9)

# train step
for epoch in range(2):
    running_loss = 0.0
    # i begin from 0
    for i, data in enumerate(trainloader, 0):
        inputs, labels = data
        inputs, labels = Variable(inputs), Variable(labels)
        optimizer.zero_grad()
        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        running_loss += loss.data[0]
        if i % 2000 == 1999:
            # print the average loss in 2000
            print('[%d, %5d] loss: %.3f' % (epoch + 1, i + 1, running_loss / 2000))
            running_loss = 0.0
        else:
            print('epoch', i, end = '\r')

print('Finish Training !')

# Test
'''
dataiter = iter(testloader)
images, labels = dataiter.next()

# show the img for us
imshow(torchvision.utils.make_grid(images))
print('GroundTruth: ', ' '.join('%5s' % classes[labels[j]] for j in range(4)))

outputs = net(Variable(images))
print(outputs.data)
# get the max from every example
_, predicted = torch.max(outputs.data, 1)
print('Predicted: ', ' '.join('%5s' % classes[predicted[j]] for j in range(4)))
'''
correct = 0
total = 0
for data in testloader:
    images, labels = data
    outputs = net(Variable(images))
    _, predicted = torch.max(outputs.data, 1)
    total += labels.size(0)
    correct += (predicted == labels).sum()

print('Accuracy of the network on the 10000 test images: %d %%' % (100 * correct / total))
