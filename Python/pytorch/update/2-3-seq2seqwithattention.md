## Sequence to Sequence with Attention

>This project is the same as the repo `mini seq2seq`, which can be found on the github

---

### 1. Introduction

为德语到英语的神经机器翻译任务最小化构建带有 Attention 机制的 Seq2Seq 模型，项目使用 PyTorch 实现，该项目的特性如下

* 模块化构建支持其他项目的封装
* 可读性的最小化实现
* 支持 `batch` 和 GPU

该实现依赖于 `torchtext` 的数据集和 `spacy` 的数据供给方式提供了最小化的数据集和预处理模块

### 2. Model description

* `Encoder`: 双向 GRU
* `Decoder`: 带有 Attention 机制的单项 GRU
* `Attention`: [Neural Machine Translation by Jointly Learning to Align and Translate](https://arxiv.org/abs/1409.0473)

### 3. Requirements

* `GPU` & `CUDA`
* `Python3`
* `PyTorch`
* `torchtext`
* `numpy`
* `spaCy`
* `Visdom`: (optional)

下载对应的数据集和模型

```bashs
sudo python3 -m spacy download de    # 德语
sudo python3 -m spacy download en    # 英语
```

### 4. Code & Notebooks

#### 4.1 `utils.py`

1. 该模块的目的在于加载并返回数据集以供训练，其中使用了 `spacy`, `torchtext` 分别提供数据集和语言方面的模型加载，其中的 `load_dataset` 函数的输入参数是 `batch size(32)`，返回参数是

   * `train_iter`: 训练集
   * `val_iter`: 验证集
   * `test_iter`: 测试集
   * `DE`: 德语语言模型
   * `EN`: 英语语言模型

2. 数据细节分析

   ​

```python
import re
import spacy
from torchtext.data import Field, BucketIterator
from torchtext.datasets import Multi30k


def load_dataset(batch_size):
    spacy_de = spacy.load('de')
    spacy_en = spacy.load('en')
    url = re.compile('(<url>.*</url>)')

    def tokenize_de(text):
        return [tok.text for tok in spacy_de.tokenizer(url.sub('@URL@', text))]

    def tokenize_en(text):
        return [tok.text for tok in spacy_en.tokenizer(url.sub('@URL@', text))]

    DE = Field(tokenize=tokenize_de, include_lengths=True,
               init_token='<sos>', eos_token='<eos>')
    EN = Field(tokenize=tokenize_en, include_lengths=True,
               init_token='<sos>', eos_token='<eos>')
    train, val, test = Multi30k.splits(exts=('.de', '.en'), fields=(DE, EN))
    DE.build_vocab(train.src, min_freq=2)
    EN.build_vocab(train.trg, max_size=10000)
    train_iter, val_iter, test_iter = BucketIterator.splits(
            (train, val, test), batch_size=batch_size, repeat=False)
    return train_iter, val_iter, test_iter, DE, EN
```

#### 4.2 `train.py`

#### 4.3 `model.py`