# PyTorch 

---

## 1. Introduction

1. 不同于 TensorFlow, PyTorch 选用动态图进行计算，最终创建的计算图取决于执行的条件分支
2. 动态图的调试方便，使用 `pdb`, `ipdb` 可以随意的调试并发现错误的地方
3. PyTorch 不同于 TensorFlow 追求最简单的抽象层次: tensor -> Variable(autograd) -> nn.Module(NN)


## 2. Begin

1. PyTorch 和 numpy 衔接非常紧密，Torch 不支持的运算可以先转化成 numpy 处理再转回来

2. tensor.type() 显示数据类型

3. 可学习参数层放在 `__init__()` 函数中并且尽量保持模型是无状态的

4. 网络的可学习参数 `net.parameters()`, `net.named_parameters()`

5. 存取网络参数

   ```python
   # only save the model parameters
   torch.save(model_object.state_dict(), 'params.pt')
   model_object.load_state_dict(torch.load('params.pt'))
   ```

   ​
