### Tensors

```python
import torch
a = torch.FloatTensor(5, 7)
a = torch.randn(5, 7)
print(a, a.size())                     # the .size return the tuple instance
```

### Inplace and Out-of-place operations

>第一个不同点在于 tensor 上的所有操作, 如果想要在 tensor 自身上进行的操作 (in-place) 就要加上一个 `_` 作为后缀. 例如, `add` 是一个 out-of-place 的 version ,而 `add_` 是一个 in-place 的 version 

```python
a.fill_(3.5)    # a change into the 3.5
b = a.add(4.0)  # a is still 3.5, but the b is 7.5
print(a, b)
```

### Autograd

>在 autograd 中, 我们引入了一个 `Variable` 类, 它是一个非常单薄 的 `Tensor` 包装器. 你可以通过 `.data` 访问到原始 tensor, 并在计算完反向之后, 求出这个变量的梯度, 并将这个梯度累加到 `.grad`属性中.
>
>还有一个对于 autograd 的使用非常重要的类 - `Function` 类. `Variable` 和 `Function` 是相互关联的, 并创建了一张无环图, 它记录一个完整的计算历史. 每个 `Variable` 的 `.grad_fn` 属性都引用了一个计算出这个Variable的函数 (除了用户创建的变量外 - 这些变量的 `.grad_fn` 为 `None` ).
>
>如果你想要计算导数, 你可以在 `Variable` 上调用 `.backward()`. 如果 `Variable` 是一个标量 (i.e. 它拥有一个tensor元素), 则不需要为 `backward()` 指定任何参数, 但是如果它包含许多的元素, 则需要指定一个 `grad_output` 参数, 来匹配 tensor 的 shape. (本质上就是一个权重)

```python
import torch
from torch.autograd import Variable
x = Variable(torch.ones(2, 2), requires_grad=True)
print(x, x.data, x.grad, x.grad_fn)

y = x + 2
z = y * y * 3      # [[27, 27], [27, 27]]
out = z.mean()     # 27

# If we use out.backward(), only after the optimizer renew the parameter can we autograd again
# If we use out.backward(retain_graph=True), we can backward many times and the .grad can be accumulative.
out.backward(retain_graph=True)
print(x.grad)      # 4.5

# backward with random weight
y.backward(torch.randn(2, 2), retain_graph=True)
```

### nn Package

#### 1. ConvNet

>在 `torch` 中的所有的网络输入数据都必须要有 `bacth` 维度，如果没有需要使用 `.unsqueeze(0)` 添加

```python
import torch
from torch.autograd import Variable
import torch.nn as nn
import torch.nn.functional as F

# 所有的网络来自于 nn.Module 基类
class MNISTConvNet(nn.Module):
    def __init__(self):
        # 在构造函数中，声明想要使用的所有的层
        # 这是你实例化所有模块的地方
        # 你可以稍后使用你在此给出的相同名称访问它们
        super(MNISTConvNet, self).__init__()
        self.conv1 = nn.Conv2d(1, 10, 5)
        self.pool1 = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(10, 20, 5)
        self.pool2 = nn.MaxPool2d(2, 2)
        self.fc1 = nn.Linear(320, 50)
        self.fc2 = nn.Linear(50, 10)

    # 这是 forward 函数, 它定义了只接受一个输入的网络结构,
    # 如果你愿意, 可以随意定义支持使用更多输入的网络结构.
    def forward(self, input):
        # 在 forward 函数中定义模型如何从输入到输出
        x = self.pool1(F.relu(self.conv1(input)))
        x = self.pool2(F.relu(self.conv2(x)))

        # 在你的创建模型的过程中, 你可以疯狂地使用任意的python代码创建你的模型结构,
        # 这些操作都是完全合法的, 并且会被autograd正确处理:
        # if x.gt(0) > x.numel() / 2:
        #      ...
        #
        # 你甚至可以做一个循环来重复使用相同的模块, 模块内部的模块不再
        # 处于临时状态, 所以你可以在 forward 时多次使用它们.
        # while x.norm(2) < 10:
        #    x = self.conv1(x)

        x = x.view(x.size(0), -1)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        return x
    
net = MNISTConvNet()
print(net)

# one sample into net
input = Variable(torch.randn(1, 1, 28, 28))
out = net(input)
print(out.size())

# one virtual tag for loss function
target = Variable(torch.LongTensor([3]))
loss_fn = nn.CrossEntropyLoss()  # LogSoftmax + ClassNLL Loss
err = loss_fn(out, target)
err.backward()

print(err)

# check the weights in the convnet
# the norm is thw ||x||2 
print(net.conv1.weight.data.norm(), net.conv1.weight.grad.data.norm())
```

>你可以在一个 `Module` 或一个 `Variable` 上注册一个函数. hook 可以是 forward hook 也可以是一个 backward hook. 当 forward 被执行后 forward hook 将会被执行. backward hook 将在执行 backward 阶段被执行. 让我们来看一个例子.

```python
# forward hook
# registe the hook for the conv2 Variables
def printnorm(self, input, output):
    # input 是将输入打包成的 tuple 的 input
    # 输出是一个 Variable. output.data 是我们感兴趣的 Tensor
    print('Inside ' + self.__class__.__name__ + ' forward')
    print('')
    print('input: ', type(input))
    print('input[0]: ', type(input[0]))
    print('output: ', type(output))
    print('')
    # we can see the tensor size in this function
    print('input size:', input[0].size())
    print('output size:', output.data.size())    
    print('output norm:', output.data.norm())

# register for the Variable
net.conv2.register_forward_hook(printnorm)

out = net(input)

# backward hook
def printgradnorm(self, grad_input, grad_output):
    print('Inside ' + self.__class__.__name__ + ' backward')
    print('Inside class:' + self.__class__.__name__)
    print('')
    print('grad_input: ', type(grad_input))
    print('grad_input[0]: ', type(grad_input[0]))
    print('grad_output: ', type(grad_output))
    print('grad_output[0]: ', type(grad_output[0]))
    print('')
    print('grad_input size:', grad_input[0].size())
    print('grad_output size:', grad_output[0].size())
    print('grad_input norm:', grad_input[0].data.norm())

net.conv2.register_backward_hook(printgradnorm)

out = net(input)
err = loss_fn(out, target)
err.backward()
```

#### 2. RNN

>重复使用  `nn.Linear`

```python
class RNN(nn.Module):

    # 你也可以在你模型的构造函数中传入参数
    def __init__(self, data_size, hidden_size, output_size):
        super(RNN, self).__init__()

        self.hidden_size = hidden_size
        input_size = data_size + hidden_size

        self.i2h = nn.Linear(input_size, hidden_size)
        self.h2o = nn.Linear(hidden_size, output_size)

    def forward(self, data, last_hidden):
        input = torch.cat((data, last_hidden), 1)
        hidden = self.i2h(input)
        output = self.h2o(hidden)
        return hidden, output


rnn = RNN(50, 20, 10)

# CuDNN can be accessed
loss_fn = nn.MSELoss()
batch_size = 10
TIMESTEPS = 5
# 创建一些假数据
batch = Variable(torch.randn(batch_size, 50))
hidden = Variable(torch.zeros(batch_size, 20))
target = Variable(torch.zeros(batch_size, 10))

loss = 0
for t in range(TIMESTEPS):
    # 是的! 你可以多次使用同一个网络,
    # 将损失相加, 并且调用 call backward!
    hidden, output = rnn(batch, hidden)
    loss += loss_fn(output, target)
loss.backward()
```

### Muti-GPU 

>数据并行是指当我们将 mini-batch 的样本分成更小的 mini-batches, 并行地计算每个更小的 mini-batches.
>
>数据并行通过使用 `torch.nn.DataParallel` 实现. 我们可以用 `DataParallel` 包装一个模块, 然后它将在 batch 维度(默认是0轴) 平分数据给多个 GPUs 进行并行计算.

refer to the document to get more ...