# Chart3

---

## Tensor

```python
Tensor(...)    # 系统不会立即分配空间，只有使用时分配空间
ones(...)
zeros(...)
eye(...)
arange(...)
linspace(...)
rand / randn(...)
normal(mean, std) / uniform(low, high)
randperm(...)    # random vector
tensor.numel()   # total number in tensor
tensor.tolist()
tensor.numpy()
tensor.size()
tensor.view(...)   # 返回的新的tensor和原来的tensor共享内存
tensor.unsqueeze(dim)
tensor.squeeze() / tensor.squeeze(dim)    # squeeze all or squeeze one special dimension
```

索引操作中得到的结果一般和原tensor共享内存，常用的选择函数

```python
tensor.index_select(dim, index)    # 对tensor在dim上应用index进行索引
tensor.masked_index(mask)
torch.non_zero(input)      # return non zero indices in tensor

# torch.gather 的输出size和index的size一样，dim是index应用的维度
# out[i][j] = input[index[i]][j]...
torch.gather(input, dim ,index)
```

数据类型

```python
tensor.int()
tensor.float()
tensor = tensor.type(torch.FloatTensor)
```

element-wise operations, size do not change

```python
abs / sqrt / div / exp / fmod / log / pow
cos / sin / asin / atan2 / cosh
ceil / round / floor / trunc
clamp(截断函数) / sigmoid / tanh / relu ...
```

归并函数，size change

```python
mean / sum / median / mode    # mean / sum / 中位数 / 模数
norm / dist    # p范数 / p范数距离差
std / var      # 标准差 / 方差
cumsum / cumprod    # 累加 / 累乘
```

比较函数

```python
a[a > 1]   # 提取数据
```

线性代数

```python
mm / bmm   # 矩阵乘法, batch 的矩阵乘法
t / svd / ...
```

广播法则是一种科学计算的经典法则，在执行快速向量化计算的时候不会占用额外的内存或者显存，和广播法则非常类似的 `torch` 操作有 `squeeze` / `unsqueeze` / `expand` / `view` / `expand_as` / `repeat`

```python
# expand 不分配新的空间，只是生成之前的视图view,所以内部共享内存
# repeat 是分配新的空间的
```

普通的索引方法只修改tensor的头信息所以速度快共享内存，但是高级索引或者其他的特殊的方式不共享内存，开辟新内存存储这些数据。

有时候有些tensor处理方法会导致数据tensor不连续，这时候使用contiguous方法可以让数据连续，但是代价就是扩展了新的数据空间(不共享内存)。

```python
torch.set_num_threads()    # 设置pytorch在进行CPU多线程并行计算的时候占用的线程数目
torch.get_num_threads()    # 获得pytorch在进行CPU多线程并行计算的时候占用的线程数目
torch.set_printoptions(...)# 设置打印的tensor的数值精度和格式
```

防止梯度爆炸

```python
torch.nn.utils.clip_grad_norm(parameters, max_norm, norm_type)  # max_norm 是最大的裁剪值，在backward之后step之前调用防止训练参数的梯度爆炸现象, norm_type 可以制定是p-norm中的p大小默认是无穷norm
```

## Autograd

* `Variable` / `Tensor` 对象中含有的 `volatile` 是 bool 类型的变量，建立在这样的变量上的计算图都不会进行求导计算只用于执行模型的前馈推理过程

* `.grad_fn` 函数的 `next_functions` 保存了对应的算子的输入的tensor的 `grad_fn` 对象，是tuple类型

* `Variable` 不存在操作对应的 replace 方法，因为反向传播的过程中需要用到这些 `Variable` / `tensor` 的值，这些数值在前馈计算过程中会保存成 buffer 但是在 backward 过程中清空(`retain_graph` 制定保存)。

* autograd 对 variable 操作构建计算图对 variable 的操作抽象为 function算子，用户创建的变量没有grad_fn但是需要求梯度并是累加的(多次反向传播)非叶子节点的梯度反向传播过程中会被清空但是可以使用 hook 查看

* 扩展 Autograd

  不止会反向传播的函数或者复杂运算可以自己编写对应的前向传播和反向传播的代码扩展 autograd