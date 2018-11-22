# nn

---

* `torch.nn` 的核心数据结构是 `Module` 是一个抽象概念，可以表示神经网络的某一个层，也可以表示一个包含很多层的神经网络

* 在自定义的 `nn.Module` 结构中，如果是自己定义的张量参数必须使用 `nn.Parameters` 包装成为模块的可学习参数，并且支持在其中插入子 `Module`, 可以自动的查询并添加子 `Module` 的可学习参数。其中类似 `nn.GRU`, `nn.Linear` 都是默认的子模块，都是可以学习的，在使用过程中可以直接添加成为新模块的可学习参数。

* `Conv.weight.data` 中的卷积核的参数大小是 `[Out_channels, In_channels, weight, height]`

* 序列化网络结构

  1. `sequential`

     ```python
     net = nn.Sequential(nn.Linear(3, 4), nn.ReLU(), nn.Linear(4, 2), nn.ReLU())

     Sequential(
       (0): Linear(in_features=3, out_features=4, bias=True)
       (1): ReLU()
       (2): Linear(in_features=4, out_features=2, bias=True)
       (3): ReLU()
     )

     # or
     net = nn.Sequebtial()
     net.add_module('module_name1', nn.Linear(3, 4))
     net.add_module('module_name2', nn.ReLU())
     net.add_module('module_name3', nn.Linear(4, 2))
     net.add_module('module_name4', nn.ReLU())

     Sequential(
       (module_name1): Linear(in_features=3, out_features=4, bias=True)
       (module_name2): ReLU()
       (module_name3): Linear(in_features=4, out_features=2, bias=True)
       (module_name4): ReLU()
     )
     ```

  2. `modelist`

     `modellist` 和 `list` 的主要区别在于 `modellist` 可以被主模型的识别出主要的学习参数，但是 list 中的 `model` 参数主模型无法识别并无法调整。

* `torch.mannel_seed(1000)` 设置 torch 的随机种子

* `loss` 函数可以看做是一种特殊的 layer , PyTorch 将这种 layer 当做是 nn.Module 的子类

* 不同层使用不同学习率

  ```python
  optimizer = optim.SGD([{'params': net.features.parameters()},
                         {'params': net.classifier.parameters(),
                          'lr':0.01}
                        ], 
                        lr = 0.00001)

  # output
  SGD (
  Parameter Group 0
      dampening: 0
      lr: 1e-05    # old lr of 0.00001
      momentum: 0
      nesterov: False
      weight_decay: 0

  Parameter Group 1
      dampening: 0
      lr: 0.01     # new lr which is defined
      momentum: 0
      nesterov: False
      weight_decay: 0
  )
  ```

* 没有可学习参数的模块可以使用 `nn.functional.xxx` 实现，但是如果模型存在可学习参数，最好使用 `nn.Module` 实例化特定的类，特殊的比如 `dropout` 层需要使用 `nn.Dropout` 实现，虽然没有可学习的参数，但是因为 `dropout` 在训练和测试阶段不同，可以使用 `model.eval` 区分

  ```python
  import torch.nn.functional as F
  # 不存在可学习参数，可以使用 functional 实现
  F.pool / F.relu / F.tanh / F.MaxPool / F.sigmoid / ...

  # 可学习参数,参数需要额外提供
  F.linear(input, mode.weight, model.bias)
  ```

* PyTorch 中的模型参数都采用了较为合理的默认初始化策略，当然也可以自定义初始化策略，尤其是我们使用 `nn.Parameters` 的时候，可以使用初始化模型 `nn.init`

* 深入理解 `nn.Module` 模块

  ```python
  Signature: nn.Module.__init__(self)
  Source:   
      def __init__(self):
          self._backend = thnn_backend
          self._parameters = OrderedDict()
          self._buffers = OrderedDict()
          self._backward_hooks = OrderedDict()
          self._forward_hooks = OrderedDict()
          self._forward_pre_hooks = OrderedDict()
          self._modules = OrderedDict()
          self.training = True
  ```

  * `_parameters`: 存储用户直接设置的 parameters 的字典，但是子模块的参数不会被识别到

  * `_modules`: 保存子模型

  * `_buffers`: 缓存，每一次反向传播需要用到前向传播的结果

  * `_backward_hooks` / `_forward_hooks`: 注册的钩子函数

    前向传播结束的时候会调用钩子函数，但是注意钩子函数绝对不可以修改内部的梯度值，主要作用在于获取中间结果，比如提取某一层的输出作为分类或者其他的用途就需要使用钩子函数。

  * `training`: BN 和 Dropout 可以决定训练和测试阶段不同策略，通过 `training` 判断前向传播的具体策略和细节，比如测试阶段 dropout 什么都不做，但是反向传播阶段是会随机失活一部分的神经元，可以直接调用模型的 `module.train` 方法设置 `traning` 属性为 True，但是 `module.eval` 设置 `traning` 属性是 False

* GPU 运行

  ```python
  model = model.cuda()    # 将模型的参数转换到 GPU 上
  input.cuda()    # 输入数据迁移到 GPU 上
  ```

  GPU 并行

  ```python
  new_net = nn.DataParallel(net, device_ids=[0, 1])   # 在0,1GPU上并行
  output = new_new(input)    # 将batch的数据切分成多份分别送入GPU运行然后将梯度相加
  ```

  ​