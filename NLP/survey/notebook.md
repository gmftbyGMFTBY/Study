# Survey of the DL in NLP

---

## 1. Introduction

1. human-craft to the data-driven which involving statistics, probability and ML, DL
2. data + algorithm help to leveraged the DL even in the NLP
3. This survey is useful for the one advanced research and practice themselves

---

## 2. NLP and DL

>DL method in the NLP

1. NLP has been influenced by a number of other fields such as linguistics, psychology,

   philosophy, cognitive science, probability and statistics, and machine learning.

2. Work in NLP can be divided into two broad sub-areas: core areas and applications

3. Core ares:

   * Language Modeling: the asscoaition among the words
   * Morphological processing: process the meaningful part of the nature language
   * Semantic processing: get the meaning of the words
   * Syntactic processing or parsing

4. Applications:(topic)

   * IR (named entites and relations from document)
   * Translation
   * Summarization
   * QA
   * Classification and clustering of documents
   * Image and video captioning

5. Early attempts at NLP were usually rule based, where rules were hand crafted using knowledge derived from various areas.

6. To satisfy the need to handle language beyond what is possible with rules written a priori, NLP began to transform slowly, starting in the 1980s, into a data-driven field predominantly using statistical and probabilistic computations along with machine learning algorithms.

7. Over time, a number of machine learning approaches such as naïve Bayes, k-nearest neighbors, hidden Markov models, conditional random fields, decision trees, random forests, and supportvector machines were widely used in NLP.  However, during the past several years, there has been a wholesale transformation in the field of NLP, and many of these approaches have been entirely replaced, or at least enhanced, by neural models, which are discussed in the following section.

8. CNN can also use in some parts of the NLP problem.

9. Much like convolutional networks, recursive networks use a form of weight sharing to minimize training. However, whereas CNNs share weights horizontally (within a layer),

   recursive nets share weights vertically (between layers). **A simple type of recursive neural network that is used heavily in NLP is the recurrent neural network (RNN)**

10. Since much of NLP is dependent on the order of words or other elements such as phonemes or sentences, it is extremely useful to have memory of the previous elements when processing new ones.

11. RNN can be benefit by the bidirectional and the stack mechanism.

12. LSTM is very effecient but **if information is disregarded, it cannot be recovered, even if its presence is desired later.** And GRU has been shown to perform as well as or better than standard LSTMs in many NLP tasks.

13. The attention machism, ReLU(include other activation function), Residual  learning,  dropout can be used to fix the problem of the Seq2Seq structure.

## 3. DL in Core NLP

---

1. The core issues of NLP are those issues that are inherently present in any computational linguistic system. In order to perform translation, text summarization, image captioning, or any other linguistic task, there must be some understanding of the underlying language. This understanding can be broken down into four main areas: **language modeling, morphology, parsing and semantics.**
2. Language modeling can be viewed in two ways. 
   1. it is the task of determining which words follow which. 
   2. By extension, however, this can be viewed as determining what words mean, as individual words are only weakly meaningful if not meaningless, deriving their full value only from their interactions with other words. 
3. Morphology is the study of how words themselves are formed. It considers the roots of words and how they evolve through the use of prefixes and suffixes, compounds, and other intraword devices, in order to display tense, gender, plurality, and a number of other linguistic constructs. 
4. Parsing considers the interactions between words. Specifically, it considers which words modify each other, and in which ways, forming constituents (i.e., phrases of various kinds), leading to a sentential structure. 
5. semantics, which is the study of what words mean as a collective. It must take into account the meanings of the individual words and how they relate to and modify others, as well as the context these words appear in and some degree of world knowledge, i.e., "common sense".

### 3.1 Language Modeling

1. Language modeling (LM) is an essential piece of almost any application of NLP, from speech recognition to machine translation. Useful for many NLP task such as translation and text summarization.
2. In essence, language modeling is the process of creating a model to predict words or simple linguistic components given previous words or components, usually with associated probabilities.
3. Early, Bag-of-words (frequency of the word in corpus) to n-gram model (statistical, the frequency of words follow each other, but increase the size of the model and computation, usually 5-gram).  
4. A major problem with statistical language(n-gram) models was their inability to deal well with synonyms or out-of-vocabulary (OOV) words. So Neural Languag model appear, Not only do they allow for the prediction of synonymous words, they also allow for modeling the relationships between words. And word embedding tech is also very effecient in LM.
5. The metric is also very important for the LM, such as WER, perplexity. Perplexity is a reasonable measurement for LMs trained on the same datasets, but when they are trained on different vocabularies, the metric becomes less meaningful. So many NLP research are used in same big dataset.
6. Key-Value Net for LM, This showed that the use of attention mechanisms, particularly those with several distinct parameters, is useful in language modeling.
7. Another recent study was done on the usage of residual memory networks (RMNs) for language modeling.It was found that increasing network depth improved results, but that when using large batch sizes, memory constraints were encountered.It was found that RMNs are capable of outperforming LSTMs of similar size.
8. convolutional neural network that was used recently in language modeling was one in which the pooling layers were replaced with fully-connected layers. And CNN can reduce the perplexity of the dataset.
9. Character Aware Neural LM is also the famous NN, the analysis also showed that the network was capable of identifying prefixes, roots, and suffixes, as well as understanding hyphenated words, making it an extremely robust model.

### 3.2 Morphology

1. Morphology is concerned with finding segments within single words, including roots and stems, prefixes, suffixes, and—in some languages—infixes
2. A model using context message is better in modeling the Morphology.

### 3.3 Parsing

1. Parsing examines how different words and phrases relate to each other within a sentence.
2. Parsing contains two major part: constituency parsing(成分句法分析), dependency parsing(依存句法分析).
   * In constituency parsing, phrasal constituents are extracted from a sentence in a hierarchical fashion. Phrases are identified, which in turn form larger phrases, eventually culminating in complete sentences.
   * Dependency parsing on the other hand looks solely at the relationships between pairs of individual words.Focous on the relations among the words.
3. Most recent uses of deep learning in natural language parsing have been in the area of dependency parsing, within which there exists another major divide in types of solutions.
   * Graph-based parsing constructs a number of parse trees that are then searched to find the correct one, which gragh-based is the generative models. based on the formal grammer.
   * More popular in recent years than graph-based approaches have been transition-based approaches.while a number of modifications have been proposed, the standard method of transition-based dependency parsing is to create a buffer containing all of the words in the sentence and stack containing only the root label. words are then pushed onto the stack, where connections, known as arcs, are made between the top two items.
4. While transition-based dependency parsing still remains successful, currently defining the state of the art, improvements have recently been attained by applying deep learning to constituency parsing and generative models. 

### 3.4  Semantics 

Semantic processing involves understanding the meaning of words, phrases, sentences, or documents at some level. Word2Vec and GloVe claim that they can capture the meaning of the words. In this section, neural semantic processing research is separated into two distinct areas: Work focusing on comparing the semantic similarity of two portions of text, and work focusing on capturing and transferring meaning in high level constituents of language, particularly sentences.

* Semantic Comparison

  One way to test the efficacy of an approach to computing semantics is to see if two similar phrases, sentences or documents, judged by humans to have similar meaning also are judged similarly by a program. 

* Sentence Modeling

   Extending from neural language modeling, which

  attempts to capture the meaning of words in vectors, sentence modeling attempts to capture the meaning of sentences in vectors.

## 4. Application of NLP using DL

