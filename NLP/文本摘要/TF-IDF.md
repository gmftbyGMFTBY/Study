## TF-IDF

词频-逆文件频率

---

>是一种统计方法，用来评估一个词对一个文件集或者语料库中其中一份语料的重要程度
>
>* 重要性随着在文件中的统计次数成正比
>* 重要性随着在语料库中的统计次数成反比
>* 倾向于过滤掉常用词 (`IDF`)
>* 无法体现词的位置信息

---

1. `TF`

   * 词频 :  

     1. 指的是某一个给定的词语在该文件中出现的次数。

     2. 这个数字通常会被归一化(一般是词频除以文章总词数), 以防止它偏向长的文件

        长文件中出现的次数可能会比短文件中出现的次数要多，我们要避免文件的大小出现对统计结果的影响

     3. 缺陷 : 但是有时候并不是出现次数多的次更会代表一个文件的情况，相反，有时候出现次数少的词更有可能代表文件的特征，这就需要我们配合使用`IDF`

   * 公式 :
     $$
     TF_w = \frac{N(w)}{N}
     $$

     * $$w$$ : 某一个单词
     * $$N(w)$$ : 单词$$w$$在文件中出现的次数
     * $$N$$ : 文件中的词条总数

2. `IDF`

   * 逆文件频率 : 

     1. 指的是语料库中包含一个词条的文件越少,`IDF`值越大，越说明词条具有良好的类别区分能力

   * 公式
     $$
     IDF_w =\log{\frac{N}{N_w + 1}}
     $$

3. `TF-IDF`
   $$
   TF-IDF=TF \times IDF
   $$



---

## 余弦相似性

1. 对文章或者句子先进行分词，构成**词袋模型**，明确词向量的维数和对应的单词

2. 将所有的句子或者文档构成词向量的形式

3. 对于文档之间的词向量模型计算**词向量夹角的大小**，比较两个文档或者句子的相似性

4. 余弦定理
   $$
   \cos{\theta}=\frac{a^2+b^2-c^2}{2ab}\\
   c^2=a^2+b^2-2ab\cos{\theta}
   $$

5. 余弦定理向量形式改写
   $$
   \left\{ \begin{array}{rcl}
   \overrightarrow{a}=(x1, y1)\\
   \overrightarrow{b}=(x2, y2)\\
   a^2 = x_1^2+y_1^2\\
   b^2=x_2^2+y_2^2\\
   c^2=(x2-x1)^2+(y2-y2)^2\\
   c^2=a^2+b^2-2|a||b|\cos{\theta}\\
   \end{array}\right.\\
   \cos{\theta}=\frac{x_1x_2+y_1y_2}{\sqrt{x_1^2+y_1^2} \times \sqrt{x_2^2+y_2^2}}
   $$
   数学家证明，这样的向量形式对于多维向量依然成立
   $$
   \overrightarrow{A} = (A_1, A_2,A_3,...,A_n)\\
   \overrightarrow{B} = (B_1, B_2,B_3,...,B_n)\\
   \cos{\theta} = \frac{\sum_{i=1}^n(A_i\times B_i)}{\sqrt{\sum_{i=2}^n(A_i^2)}\times \sqrt{\sum_{i=2}^n(B_i^2)}}=\frac{\overrightarrow{A} \cdot \overrightarrow{B}}{|A|\times |B|}
   $$

6. 余弦定理计算的结果越接近1，说明夹角 $$\theta$$ 越接近 0,向量的相似度越高

7. **使用余弦相似度和TF-IDF找出文本的相似度**

   1. `TF-IDF` : 计算文章的关键词
   2. 抽取或者不抽取的对与文章中的关键词构建一个词袋向量，计算词频
   3. 对词频的词向量计算余弦相似度，值越大相似度越高

---

## 自动摘要技术

>本笔记是基于词频的自动摘要技术

1. 1958年的IBM公司科学家[H.P. Luhn](http://en.wikipedia.org/wiki/Hans_Peter_Luhn)的论文[《The Automatic Creation of Literature Abstracts》](http://www.di.ubi.pt/%7Ejpaulo/competence/general/%281958%29Luhn.pdf)对于这种自动摘要技术首次进行了说明

2. 博士认为，文章的信息都包含在文章的句子中，只不过是有的句子包含的信息比较少，有的句子包含的信息比较多罢了，自动摘要就是找出包含信息比较多的句子

3. 句子的信息量使用关键词来衡量，关键词越多，说明句子越重要

4. 博士引入了新的概念

   **簇** : 

   * 包含多个关键字的句子片段
   * 只要关键词之间的距离小于一个阈值被认为处在同一个**簇**中

   ![簇](/home/lantian/File/Study/NLP/文本摘要/簇.png)

5. **簇**的评分

   $$
   Importance = \frac{N(w)^2}{N}	
   $$

   * $$Importance$$ : 簇的重要性评分
   * $$N(w)$$ : 簇中包含的关键字的数量
   * $$N$$ : 簇的长度
   * 将文章中所有**包含最高簇的句子**合在一起就是一个文章的自动摘要

6. 算法简化

   ```python
   　Summarizer(originalText, maxSummarySize):

   　　　　// 计算原始文本的词频，生成一个数组，比如[(10,'the'), (3,'language'), (8,'code')...]
   　　　　wordFrequences = getWordCounts(originalText)

   　　　　// 过滤掉停用词，数组变成[(3, 'language'), (8, 'code')...]
   　　　　contentWordFrequences = filtStopWords(wordFrequences)

   　　　　// 按照词频进行排序，数组变成['code', 'language'...]
   　　　　contentWordsSortbyFreq = sortByFreqThenDropFreq(contentWordFrequences)

   　　　　// 将文章分成句子
   　　　　sentences = getSentences(originalText)

   　　　　// 选择关键词首先出现的句子
   　　　　setSummarySentences = {}
   　　　　foreach word in contentWordsSortbyFreq:
   　　　　　　firstMatchingSentence = search(sentences, word)
   　　　　　　setSummarySentences.add(firstMatchingSentence)
   　　　　　　if setSummarySentences.size() = maxSummarySize:
   　　　　　　　　break

   　　　　// 将选中的句子按照出现顺序，组成摘要
   　　　　summary = ""
   　　　　foreach sentence in sentences:
   　　　　　　if sentence in setSummarySentences:
   　　　　　　　　summary = summary + " " + sentence

   　　　　return summary
   ```

7. `Python`实现链接

   [Python实现](https://github.com/ptwobrussell/Mining-the-Social-Web/blob/master/python_code/blogs_and_nlp__summarize.py)

   ​