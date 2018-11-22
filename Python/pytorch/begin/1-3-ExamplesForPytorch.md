# Examples

>Pytorch 两个主要的优点:
>
>* 类似 numpy 的 n 维张量但是可以在 GPU 上运行
>* 建立和训练神经网络自动微分

## Tensors

### 1. Numpy for NN

```PYTHON
import numpy as np

# N 是一个batch的样本数量; D_in是输入维度;
# H 是隐藏层向量的维度; D_out是输出维度.
N, D_in, H, D_out = 64, 1000, 100, 10

# 创建随机的输入输出数据
x = np.random.randn(N, D_in)
y = np.random.randn(N, D_out)

# 随机初始化权重参数
w1 = np.random.randn(D_in, H)
w2 = np.random.randn(H, D_out)

learning_rate = 1e-6
for t in range(500):    
    # 前向计算, 算出y的预测值
    h = x.dot(w1)
    h_relu = np.maximum(h, 0)
    y_pred = h_relu.dot(w2)

    # 计算并打印误差值
    loss = np.square(y_pred - y).sum()
    print(t, loss)

    # 在反向传播中, 计算出误差关于w1和w2的导数
    grad_y_pred = 2.0 * (y_pred - y)
    grad_w2 = h_relu.T.dot(grad_y_pred)
    grad_h_relu = grad_y_pred.dot(w2.T)
    grad_h = grad_h_relu.copy()
    grad_h[h < 0] = 0
    grad_w1 = x.T.dot(grad_h)

    # 更新权重
    w1 -= learning_rate * grad_w1
    w2 -= learning_rate * grad_w2
```

### 2. Pytorch for NN

```PYTHON
import torch

dtype = torch.FloatTensor
# dtype = torch.cuda.FloatTensor # 取消注释以在GPU上运行

# N 批量大小; D_in是输入尺寸;
# H是隐藏尺寸; D_out是输出尺寸.
N, D_in, H, D_out = 64, 1000, 100, 10

# 创建随机输入和输出数据
x = torch.randn(N, D_in).type(dtype)
y = torch.randn(N, D_out).type(dtype)

# 随机初始化权重
w1 = torch.randn(D_in, H).type(dtype)
w2 = torch.randn(H, D_out).type(dtype)

learning_rate = 1e-6
for t in range(500):
    # 正向传递：计算预测y
    h = x.mm(w1)
    h_relu = h.clamp(min=0)
    y_pred = h_relu.mm(w2)

    # 计算并打印loss
    loss = (y_pred - y).pow(2).sum()
    print(t, loss)

    # 反向传播计算关于损失的w1和w2的梯度
    grad_y_pred = 2.0 * (y_pred - y)
    grad_w2 = h_relu.t().mm(grad_y_pred)
    grad_h_relu = grad_y_pred.mm(w2.t())
    grad_h = grad_h_relu.clone()
    grad_h[h < 0] = 0
    grad_w1 = x.t().mm(grad_h)

    # 使用梯度下降更新权重
    w1 -= learning_rate * grad_w1
    w2 -= learning_rate * grad_w2
```

## Autograd

>在上面的例子中, 我们不得不手写实现神经网络的正反向传播的代码. 而手写实现反向传播的代码对于一个 小型的双层网络来说是没什么大问题的, 但是在面对大型复杂网络手写方向传播代码就会变得很棘手.
>
>谢天谢地, 我们可以使用 [自动微分](https://en.wikipedia.org/wiki/Automatic_differentiation) 来自动化的计算神经网络中的后向传播. PyTorch 中的 **autograd**包提供自动微分了这个功能. 使用 `autograd` 时, 网络的正向传播将定义一个 **计算图** ; Tensor 将会成为图中的节点,从输入 Tensor 产生输出 Tensor 的函数将会用图中的( Edge )依赖边表示. 通过计算图来反向传播可以让您轻松计算梯度.
>
>这听起来很复杂, 但是在实践中使用起来相当简单. 我们将 `PyTorch` 的 Tensor 包装成在 **Variable** 对象； 一个 Variable 代表一个计算图中的节点. 如果 `x` 是一个 Variable , 则 `x.data` 是一个 Tensor , 而 `x.grad` 是另外一个包含关于 `x` 的梯度的 `Variable` .
>
>`PyTorch Variable` 与 `PyTorch Tensor` 具有相同的 API: (几乎) 任何您可以在 Tensor 上执行的操作也适用于 Variable ；该区别在于如果你使用 `Variable` 定义了一个计算图, Pytorch 允许您自动计算梯度.
>
>这里我们使用 PyTorch 的 `Variable` 和自动微分来实现我们的双层网络；现在我们不再需要手写任何关于 计算网络反向传播的代码:

```python
# -*- coding: utf-8 -*-
import torch
from torch.autograd import Variable

dtype = torch.FloatTensor
# dtype = torch.cuda.FloatTensor # 取消注释以在GPU上运行

# N 批量大小; D_in是输入尺寸;
# H是隐藏尺寸; D_out是输出尺寸.
N, D_in, H, D_out = 64, 1000, 100, 10

# 创建随机张量来保存输入和输出,并将它们包装在变量中.
# 设置requires_grad = False, 因为在后向传播时, 我们并不需要计算关于这些变量的梯度
# 只需要计算神经网络中的权重的梯度即可，就是下面的 w1, w2
x = Variable(torch.randn(N, D_in).type(dtype), requires_grad=False)
y = Variable(torch.randn(N, D_out).type(dtype), requires_grad=False)

# 为权重创建随机张量,并将其包装在变量中.
# 设置requires_grad = True, 因为在后向传播时, 我们需要计算关于这些变量的梯度
w1 = Variable(torch.randn(D_in, H).type(dtype), requires_grad=True)
w2 = Variable(torch.randn(H, D_out).type(dtype), requires_grad=True)

learning_rate = 1e-6
for t in range(500):
    # 正向传递:使用变量上的运算来计算预测的y; 这些
    # 与我们用于计算使用张量的正向传递完全相同,
    # 但我们不需要保留对中间值的引用,
    # 因为我们没有实现向后传递.
    y_pred = x.mm(w1).clamp(min=0).mm(w2)

    # 使用变量上的操作计算和打印损失.
    # 现在损失是形状变量 (1,) 并且 loss.data 是标量形状的张量
    # (1,); loss.data[0] 是持有损失的标量值.
    loss = (y_pred - y).pow(2).sum()
    print(t, loss.data[0])

    # 使用autograd来计算反向传递. 
    # 该调用将使用requires_grad = True来计算相对于所有变量的损失梯度.
    # 在这次调用之后 w1.grad 和 w2.grad 将是变量
    # 它们分别相对于w1和w2保存损失的梯度.
    loss.backward()

    # 使用梯度下降更新权重; w1.data 和 w2.data 是张量,
    # w1.grad 和 w2.grad 是变量并且 w1.grad.data 和 w2.grad.data 
    # 是张量.
    w1.data -= learning_rate * w1.grad.data
    w2.data -= learning_rate * w2.grad.data

    # 更新权重后手动将梯度归零
    w1.grad.data.zero_()
    w2.grad.data.zero_()
```

## Define a new Autograd function

>在这层覆盖下, 每个原始的 autograd 操作符实际上是两个函数在张量上运行. **前向传播** 函数从输入的 Tensor 计算将要输出的 Tensor . **后向传播** 函数接收上一个 Tensor 关于 scalar 的梯度, 以 及计算当前输入 Tensor 对相同 scalar 值的梯度.
>
>在 PyTorch 中, 我们可以通过定义一个 `torch.autograd.Function` 的子类和 实现 `前向传播` 和 `后向传播` 函数来轻松定义自己的 autograd 操作符. 然后我们可以 使用我们新的 autograd 操作符构造一个实例并将其作为一个函数调用, 传递用 Variable 包装了的输入数据进入到函数中去执行自动微分.
>
>在这个例子中我们定义了我们自己的 autograd 函数来执行 ReLU 非线性函数, 并用它来实现我们的双层网络:

```python
import torch
from torch.autograd import Variable

class MyReLU(torch.autograd.Function):
    """
    我们可以通过子类实现我们自己定制的autograd函数
    torch.autograd.Function和执行在Tensors上运行的向前和向后通行证.
    """

    @staticmethod
    def forward(ctx, input):
        """
        在正向传递中,我们收到一个包含输入和返回张量的张量,其中包含输出.
        ctx是一个上下文对象,可用于存储反向计算的信息.
        您可以使用ctx.save_for_backward方法缓存任意对象以用于后向传递.
        """
        ctx.save_for_backward(input)    # 这里的 save 在 backward 中要取出来
        return input.clamp(min=0)

    @staticmethod
    def backward(ctx, grad_output):
        """
        在后向传递中,我们收到一个张量,其中包含相对于输出的损失梯度,
        我们需要计算相对于输入的损失梯度.
        grad_output 就是链式求导中的后面的梯度计算
        方块是 Variable, 横线是 autograd 函数
         ____           ___          ___            _____
        |    |  mm w1  |   |  relu  |    |  mm w2  |     |
        | In |-------->| h |------->| h' |-------->| out |
        |____|         |___|        |___ | 		   |_____|
        
        对 relu 来说，grad_output 就是 h' 传播的梯度，返回的梯度传播给 mm w1 的 autograd 函数
        """
        input, = ctx.saved_tensors
        grad_input = grad_output.clone()
        grad_input[input < 0] = 0
        return grad_input


dtype = torch.FloatTensor
# dtype = torch.cuda.FloatTensor # 取消注释以在GPU上运行

# N 批量大小; D_in是输入尺寸;
# H是隐藏尺寸; D_out是输出尺寸.
N, D_in, H, D_out = 64, 1000, 100, 10

# 创建随机张量来保存输入和输出,并将它们包装在变量中.
x = Variable(torch.randn(N, D_in).type(dtype), requires_grad=False)
y = Variable(torch.randn(N, D_out).type(dtype), requires_grad=False)

# 为权重创建随机张量,并将其包装在变量中.
w1 = Variable(torch.randn(D_in, H).type(dtype), requires_grad=True)
w2 = Variable(torch.randn(H, D_out).type(dtype), requires_grad=True)

learning_rate = 1e-6
for t in range(500):
    # 为了应用我们的函数,我们使用Function.apply方法.我们把它称为'relu'.
    relu = MyReLU.apply

    # 正向传递:使用变量上的运算来计算预测的y; 
    # 我们使用我们的自定义autograd操作来计算ReLU.
    y_pred = relu(x.mm(w1)).mm(w2)

    # 计算和打印损失
    loss = (y_pred - y).pow(2).sum()
    print(t, loss.data[0])

    # 使用autograd来计算反向传递.
    loss.backward()

    # 使用梯度下降更新权重
    w1.data -= learning_rate * w1.grad.data
    w2.data -= learning_rate * w2.grad.data

    # 更新权重后手动将梯度归零
    w1.grad.data.zero_()
    w2.grad.data.zero_()
```

## torch.nn

>计算图( Computational graphs )和 autograd 是一个非常强大的定义复杂的运算符并自动地导出的范式；然而对于 大型的神经网络, 原始的 autograd 仍然显得有点太低级.
>
>当我们创建神经网络时, 我们经常思考如何设计安排 **layer** , 以及一些在训练过程中网络会学习到的 **learnable parameters**
>
>在TensorFlow中, 像 [Keras](https://github.com/fchollet/keras), [TensorFlow-Slim](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/contrib/slim), 和 [TFLearn](http://tflearn.org/) 通过构建对神经网络有用的原始计算图提供更高层次的抽象.
>
>在 PyTorch 中, `nn` 包起了同样的作用. `nn` 包定义了一组 **Modules** , 大致相当于神经网络层. 模块接收输入变量并进行计算输出变量, 但也可以保持内部状态, 如用 Variable 包装的 `learnable parameters` . `nn` 包 也定义了一系列在训练神经网络时比较常用的损失函数.在这个例子中, 我们使用 `nn` 包来实现我们的双层神经网络:

```python
import torch
from torch.autograd import Variable

# N 批量大小; D_in是输入尺寸;
# H是隐藏尺寸; D_out是输出尺寸.
N, D_in, H, D_out = 64, 1000, 100, 10

# 创建随机张量来保存输入和输出,并将它们包装在变量中.
x = Variable(torch.randn(N, D_in))
y = Variable(torch.randn(N, D_out), requires_grad=False)

# 使用nn包将我们的模型定义为一系列图层. 
# nn.Sequential是一个包含其他模块的模块,并将它们按顺序应用以产生其输出.
# 每个线性模块使用线性函数计算来自输入的输出,并保存内部变量的权重和偏差.
model = torch.nn.Sequential(
    torch.nn.Linear(D_in, H),
    torch.nn.ReLU(),
    torch.nn.Linear(H, D_out),
)

# nn包还包含流行损失函数的定义; 
# 在这种情况下,我们将使用均方差(MSE)作为我们的损失函数.
loss_fn = torch.nn.MSELoss(size_average=False)

learning_rate = 1e-4
for t in range(500):
    # 正向传递:通过将 x 传递给Sequential模型来计算预测的y.
    # 模块对象会覆盖__call__运算符,因此您可以将它们称为函数.
    # 这样做时,您将输入数据的变量传递给模块,并生成输出数据的变量.
    y_pred = model(x)

    # 计算和打印损失.
    # 我们传递包含y的预测值和真值的变量,并且损失函数返回包含损失的变量.
    loss = loss_fn(y_pred, y)
    print(t, loss.data[0])

    # 在运行反向传递之前将梯度归零.全部的可学习参数全部清空
    model.zero_grad()

    # 向后传递:计算相对于模型的所有可学习参数的损失梯度.
    # 在内部,每个模块的参数都存储在变量require_grad = True中,
    # 因此该调用将计算模型中所有可学习参数的梯度.
    loss.backward()

    # 使用梯度下降更新权重.
    # 每个参数都是一个变量,所以我们可以像我们以前那样访问它的数据和梯度.
    for param in model.parameters():
        param.data -= learning_rate * param.grad.data
```

## optim

>到目前为止, 我们一直通过手动更新的方法更新模型的可学习参数( learnable parameters )的权重 `.data` 这对于简单的优化算法像随机梯度下降来还算轻松, 但是在实际中我们经常使用更巧妙的优化器来训练神经网络, 如 AdaGrad, RMSProp, Adam 等.
>
>PyTorch 中的 `optim` 包包含了一些优化器的算法, 并提供了一些常用优化器的使用.在这个例子中, 虽然我们将像之前一样使用 `nn` 包来定义我们的模型, 但是我们这次将使用由 `optim`包提供的Adam算法来更新模型:

```python
import torch
from torch.autograd import Variable

# N 批量大小; D_in是输入尺寸;
# H是隐藏尺寸; D_out是输出尺寸.
N, D_in, H, D_out = 64, 1000, 100, 10

# 创建随机张量来保存输入和输出,并将它们包装在变量中.
x = Variable(torch.randn(N, D_in))
y = Variable(torch.randn(N, D_out), requires_grad=False)

# 使用nn包来定义我们的模型和损失函数.
model = torch.nn.Sequential(
    torch.nn.Linear(D_in, H),
    torch.nn.ReLU(),
    torch.nn.Linear(H, D_out),
)
loss_fn = torch.nn.MSELoss(size_average=False)

# 使用优化包来定义一个优化器,它将为我们更新模型的权重.
# 在这里,我们将使用 Adam;这个 optim 包包含许多其他优化算法.
# Adam构造函数的第一个参数告诉优化器应该更新哪个Variables.
learning_rate = 1e-4
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
for t in range(500):
    # 正向传递:通过将x传递给模型来计算预测的y.
    y_pred = model(x)

    # 计算和打印损失函数.
    loss = loss_fn(y_pred, y)
    print(t, loss.data[0])

    # 在向后传递之前,使用优化器对象为其要更新的变量（这是模型的可学习权重）的所有梯度归零.
    # 这是因为默认情况下,只要调用.backward(),梯度就会在缓冲区中累积(即不会被覆盖).
    # 查看torch.autograd.backward的文档以获取更多详细信息.
    optimizer.zero_grad()

    # 向后传递:计算损失函数相对于模型参数的梯度
    loss.backward()

    # 在优化器上调用step函数会更新其参数
    optimizer.step()
```

## Custom nn Modules

>有时你会想要使用比现有模块组合更复杂的特殊模型；对于这些情况, 你可以 通过继承 `nn.Module`来定义你自己的模块, 并定义一个 `forward` 来实现模块接收输入 `Variable` 并在其中(`forward`)使用其他模块输出的 `Variable` 和其他 `autograd` 操作.
>
>在这个例子中, 我们使用了我们之前已经实现的双层网络来作为一个自定义的模块子类

```python
import torch
from torch.autograd import Variable

class TwoLayerNet(torch.nn.Module):
    def __init__(self, D_in, H, D_out):
        """
        在构造函数中,我们实例化两个nn.Linear模块并将它们分配为成员变量.
        """
        super(TwoLayerNet, self).__init__()
        self.linear1 = torch.nn.Linear(D_in, H)
        self.linear2 = torch.nn.Linear(H, D_out)

    def forward(self, x):
        """
        在forward函数中,我们接受一个变量的输入数据,我们必须返回一个变量的输出数据.
        我们可以使用构造函数中定义的模块以及变量上的任意运算符.
        """
        h_relu = self.linear1(x).clamp(min=0)
        y_pred = self.linear2(h_relu)
        return y_pred


# N 批量大小; D_in是输入尺寸;
# H是隐藏尺寸; D_out是输出尺寸.
N, D_in, H, D_out = 64, 1000, 100, 10

# 创建随机张量来保存输入和输出,并将它们包装在变量中. 
x = Variable(torch.randn(N, D_in))
y = Variable(torch.randn(N, D_out), requires_grad=False)

# 通过实例化上面定义的类来构建我们的模型
model = TwoLayerNet(D_in, H, D_out)

# 构建我们的损失函数和优化器. 
# 对SGD构造函数中的model.parameters()的调用将包含作为模型成员的两个nn.Linear模块的可学习参数.
criterion = torch.nn.MSELoss(size_average=False)
optimizer = torch.optim.SGD(model.parameters(), lr=1e-4)
for t in range(500):
    # 正向传递：通过将x传递给模型来计算预测的y
    y_pred = model(x)

    # 计算和打印损失
    loss = criterion(y_pred, y)
    print(t, loss.data[0])

    # 梯度置零, 执行反向传递并更新权重.
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
```

## 控制流动态图和权重共享

>作为一个动态图和权值共享的例子, 我们实现一个奇葩的模型: 随机1-4次重复搭建同个正向传播的全连接的 ReLU 网络, 并且多个隐藏层使用相同的权重.
>
>对于这个模型, 我们可以使用普通的 Python流程控制语句来实现循环, 而且我们可以在定义前向传播时通过简单地重复使用相同的模块实现 middle_linear 层的权重共享.
>
>我们可以很容易地将这个模型作为 Module 子类来实现:

```python
import random
import torch
from torch.autograd import Variable

class DynamicNet(torch.nn.Module):
    def __init__(self, D_in, H, D_out):
        """
        在构造函数中,我们构造了三个nn.Linear实例,我们将在正向传递中使用它们.
        两个隐含层
        """
        super(DynamicNet, self).__init__()
        self.input_linear = torch.nn.Linear(D_in, H)
        self.middle_linear = torch.nn.Linear(H, H)
        self.output_linear = torch.nn.Linear(H, D_out)

    def forward(self, x):
        """
        动态图
        对于模型的正向通道,我们随机选择0,1,2或3,
        并重复使用多次计算隐藏层表示的middle_linear模块.

        由于每个正向通道都会生成一个动态计算图,因此在定义模型的正向通道时,
        我们可以使用普通的Python控制流操作符(如循环或条件语句).

        在这里我们也看到,定义计算图时多次重复使用相同模块是完全安全的.权重是共享的
        这是Lua Torch的一大改进,每个模块只能使用一次.
        """
        h_relu = self.input_linear(x).clamp(min=0)
        for _ in range(random.randint(0, 3)):
            h_relu = self.middle_linear(h_relu).clamp(min=0)
        y_pred = self.output_linear(h_relu)
        return y_pred


# N 批量大小; D_in是输入尺寸;
# H是隐藏尺寸; D_out是输出尺寸.
N, D_in, H, D_out = 64, 1000, 100, 10

# 创建随机张量来保存输入和输出,并将它们包装在变量中.
x = Variable(torch.randn(N, D_in))
y = Variable(torch.randn(N, D_out), requires_grad=False)

# 通过实例化上面定义的类来构建我们的模型
model = DynamicNet(D_in, H, D_out)

# 构建我们的损失函数和优化器.
# 用随机梯度下降训练这个奇怪的模型非常困难,所以我们使用动量
criterion = torch.nn.MSELoss(size_average=False)
optimizer = torch.optim.SGD(model.parameters(), lr=1e-4, momentum=0.9)
for t in range(500):
    # 正向传递:通过将x传递给模型来计算预测的y
    y_pred = model(x)

    # 计算和打印损失
    loss = criterion(y_pred, y)
    print(t, loss.data[0])

    # 零梯度执行反向传递并更新权重.
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
```

