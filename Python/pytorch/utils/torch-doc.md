# PyTorch Doc 

[TOC]

---

## A

---

## B

---

## C

1. `torch.contiguous()`

   返回内存连续的 Tensor 对象，如果对象本身是连续的返回自身，这个函数只是为了保证 Tensor 对象在内存中是连续的，是为了训练时候的性能考虑。

   ```python
   a = torch.Tensor(2, 2)
   b = a.contiguous()
   # return the True, means the origin Tensor is contiguous
   print(a is b)
   ```

   有时候会在报错的时候提示，在 `view` 之前需要使用 `contiguous` 函数

2. ​

---

## D

---

## E

---

## F

---

## G

---

## H

---

## I

1. `torch.index_select(input, dim, index, out=None)`

   沿着指定的

2. ​

---

## G

---

## K

---

## L

1. `torch.load(f, map_location=None, pickle_module)`

   * `f`: a file-like object
   * default to return the object to the CPU, can also be used for the GPU

   ```python
   with open(file_name, 'rb') as f:
       return torch.load(f)
   ```

2. ​

---

## M

---

## N

1. `torch.narrow(dim, start, length)`

   表示取出 Tensor 中第 dim 维上索引从 start 开始到 start + length - 1 的所有元素放在 data 中

   ```python
   x = torch.Tensor([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
   x.narrow(0, 0, 2)
   # tensor([[1, 2, 3],
   #         [4, 5, 6]])

   x.narrow(1, 1, 2)
   # tensor([[2, 3],
   #		  [5, 6],
   #         [8, 9]])
   ```

   ​

2. ​

---

## O

---

## P

---

## Q

---

## R

---

## S

1. `torch.save(obj, f, pickle_module)`

   * `obj`: saved object
   * `f`: a file-like object

   ```python
   with open(file_name, 'wb') as f:
       torch.save(model, f)
   ```

2. ​

---

## T

---

## U

---

## V

---

## W

---

## X

---

## Y

---

## Z

---
