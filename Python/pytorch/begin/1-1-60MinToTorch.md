### Import torch in Python

```Python
import torch
```

### Tensor and Size

```python
x = torch.Tensor(5, 3)
x = torch.FloatTensor(5, 3)
x = torch.rand(5, 3)                        # torch.randn -> mean=0, var=1 , torch.rand uniform from [0, 1)
x.size()                                    # the tuple subinstance
```

### Operations

```python
y = torch.rand(5, 3)
print(x + y)                                # torch.add(x, y), y.add(x) do not change the Tensor y
y.add(x)                                    # the add means the real operations on the data itself
result = torch.Tensro(5, 3)
torch.add(x, y, out = result)               # result must be defined before
print(result)

x[:, 1]                                     # all the index operations same as the Numpy

x = torch.rand(4, 4)                        # view is the reshape operations in torch
y = x.view(16)
z = x.view(-1, 8)
print(x.size(), y.size(), z.size())  

x.fill_(4)                                  # fill the tensor wth 4
torch.mm(tensor1, tensor2)                  # matrix multiply
torch.dot(tensor1, tensor2)                 # 1-D vector dot multiply
torch.linspace(begin, end, count)           # same as the numpy
```

### Used with Numpy

```python
# Tensor to Numpy
x = torch.ones(5)
y = x.numpy()
y[0] = -1000                                # Tensor also change

# Numpy to Tensor, share the memory, If do not want to share the memory, can use torch.Tensor(ndarray)
x = np.ones(4, 4)
y = torch.from_numpy(x)
x[0] = -1000                                # Tensor also change
```

### CUDA Tensor

```python
if torch.cuda.is_available():
    x = x.cuda()                            # copy the Tensor to the CUDA 
    y = y.cuda()
    x + y
```

### Autograd

>`Autograd` module has the `Variable` and `Function` for the `PyTorch`, `Variable` pack the Tensor and support almost every operations of Tensor, after that define use `.backward()` to autograd
>
>`Variable` has 3 core elements: `.data`, `.grad`, `.grad_fn`
>
>If the Tensor of the Variable is created by the operations such as +, -, *, /, ..., it has .grad_fn for the backward

```python
from torch.autograd import Variable

# x do not have the .grad_fn (not created by operations), requires_grad decide whether the Variable in the compute graph to backforward
x = Variable(torch.ones(2, 2), requires_grad = True)    
y = x + 2
z = y * y * 3
out = z.mean()                              # z and y have the .grad_fn (created by operations)
print(z, out)
```

### Gradient

> The gradient for the Variable, as before, need to get the $$\frac{d(out)}{dx}$$, bz x is the Variable (x, y, z, are all the Variable, but x is original)
>
> Must be attention that the `.backward(param)` param's shape must be same as the y, the numebr in the param means the multiple number, the weight for the `y` to backward

```python
out.backward()                              # get the grad for the x
print(x, x.grad)                            # x.grad come up

# the out is the scale so the number default is 1
# the follow line means: y = 2 * y1 + 3 * y2 and y1 = x0 + x0, y2 = x1 + x1
# such as the x0's gradient is 2 * 1 = 2, but x1's gradient is 3 * 1 = 3
y = x.sum(1)                                # sum on the axis=1
y.backward(torch.Tensor([2, 3]))
```

### Neural Networks

> Autograd can use to do backward but we often use `torch.nn` to build it quickly
>
> `torch.nn.Module` is the class need to be used to build our own NN
>
> the `forward` function is the most important function that need to use to forward calculating, and the `backward` can be calculate automaticly.

### Create NN

```python
import torch
from torch.autograd import Variable
import torch.nn as nn
import torch.nn.functional as F

class Net(nn.Module):
    # the bacth size must exist, even the input is 1 sample
    def __init__(self):
        # must call the super to init 
        super(Net, self).__init__()
        # 卷积层 '1'表示输入图片为单通道, '6'表示输出通道数, '5'表示卷积核为5*5
        self.conv1 = nn.Conv2d(1, 6, 5)
    	self.conv2 = nn.Conv2d(6, 16, 5)
    	# 仿射层/全连接层: y = Wx + b
    	self.fc1 = nn.Linear(16 * 5 * 5, 120)
    	self.fc2 = nn.Linear(120, 84)
    	self.fc3 = nn.Linear(84, 10)

	def forward(self, x):
    	# conv -> relu -> pooling 
    	x = F.max_pool2d(F.relu(self.conv1(x)), (2, 2))
    	x = F.max_pool2d(F.relu(self.conv2(x)), 2)
   	 	x = x.view(-1, self.num_flat_features(x))    # reshape to only 2 dim (batch, squeeze for the Linear)
   		x = F.relu(self.fc1(x))
    	x = F.relu(self.fc2(x))
    	x = self.fc3(x)
    	return x

	def num_flat_features(self, x):
    	size = x.size()[1:]  # 除批量维度外的所有维度
    	num_features = 1
    	for s in size:
        	num_features *= s
    	return num_features

net = Net()
print(net)
```

### Explaination

```python
net.parameters()                                # get the param of the net
net.named_parameters()                          # return the name and the param
```

### Use the NN

```python
# forward
input = Variable(torch.randn(1, 1, 32, 32))
out = net(input)

# backward
net.zero_grad()                                 # clear the grad
out.backward(torch.randn(1, 10))                # the multiple weight for the gradient

# loss function
target = Variable(torch.arange(1, 11))          # need to be careful of the Tensor size and dtype
criterion = nn.MSELoss()                        # can be the MSELoss
loss = criterion(out, target)
print(loss)
loss.grad_fn.next_functions()                   # get the before functions
net.zero_grad()                                 # clear before backward
loss.backward()

# renew the paramters
# SGD: weight -= lr * gradient
# you can define the renew function yourself , but the `torch.optim` is accessed
import torch.optim as optim
# 新建一个优化器，并指定优化的参数和学习率
optimizer = optim.SGD(net.parameters(), lr = 0.01)   
# 优化过程
optimizer.zero_grad()                           # 首先梯度清零(与 net.zero_grad() 效果一样)
output = net(input)
loss = criterion(output, target)
loss.backward()
optimizer.step()                                # core step: 更新参数
```

### Data

> In pytorch, you do not need to study the data loader which in tensorflow, you can use any package for python to load your data, you only need to load it into `numpy` and `torch.Tensor`
>
> In vision, the `torchvision` have lots of dataset such as `CIFAR10`, `MNIST`, `ImageNet` and these loaders can provide the convience for the torch users.

### Pytorch on GPU

> Move all the Tensor and Variable into GPU only need to use `.cuda` (tranfer the data to GPU), `.cpu` (transfer the data to CPU)
>
> `.cuda(index)`, can search the different GPUs or use `os.environ['CUDA_VISIBLE_DEVICES'] = '1'`

```python
net.cuda(index)                                 # transfer all the parameters in the nn to the GPU Tensor
inputs, labels = Variable(inputs.cuda()), Variable(labels.cuda())

# IPython can test these two lines
torch.cuda.is_avaiable()                        # judge the cuda can be used on the computer
torch.cuda.device_count()                       # count the number of the GPU
```

### The NN example for the CIFAR10 is avaiable in `cifar10_test.py`

