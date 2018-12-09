#!/usr/bin/python3

'''Simple Classifier for CIFAR-10'''

import ipdb
import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision as tv
import torchvision.transforms as transforms
from torchvision.transforms import ToPILImage
from torch import optim
from torch.autograd import Variable

show = ToPILImage()    # change Tensor to Image, show the picture

transform = transforms.Compose([
    transforms.ToTensor(),    # change to Tensor
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))    # normalization
    ])

trainset = tv.datasets.CIFAR10(
        root='/home/lantian/Downloads/dataset/cifar',
        train=True,
        download=True,
        transform=transform)

trainloader = torch.utils.data.DataLoader(
        trainset,
        batch_size=4,
        shuffle=True,
        num_workers=2)

testset = tv.datasets.CIFAR10(
        '/home/lantian/Downloads/dataset/cifar',
        train=False,
        download=True,
        transform=transform)

testloader = torch.utils.data.DataLoader(
        testset,
        batch_size=4,
        shuffle=False,
        num_workers=2)

classes = ('plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(3, 6, 5)
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        x = F.max_pool2d(F.relu(self.conv1(x)), (2, 2))
        x = F.max_pool2d(F.relu(self.conv2(x)), 2)
        x = x.view(x.size()[0], -1)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

if __name__ == "__main__":
    net = Net()
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(net.parameters(), lr = 0.001, momentum=0.9)

    '''
    for epoch in range(2):
        running_loss = 0.0
        for i, data in enumerate(trainloader, 0):
            inputs, labels = data
            inputs, labels = Variable(inputs), Variable(labels)

            optimizer.zero_grad()

            outputs = net(inputs)
            loss = criterion(outputs, labels)

            loss.backward()
            optimizer.step()
            running_loss += loss.item()

            if i % 2000 == 1999:
                print('[%d, %5d] loss: %.3f' % (epoch + 1, i + 1, running_loss / 2000))
                running_loss = 0.0

    print('Finish traning ...')
    '''
    # torch.save(net.state_dict(), 'cifar10.pt')
    net.load_state_dict(torch.load('cifar10.pt'))
    # test
    correct, total = 0, 0
    for data in testloader:
        images, labels = data
        outputs = net(Variable(images))
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum()

    print('10000 test score: %d %%' % (100 * correct / total))
