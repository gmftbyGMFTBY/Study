
***

[TOC]

## 总览

* 问题描述
* 问题分析
  * 简化及优化装箱过程的 **BLF 思想**的应用
  * 问题的理解
* PSO算法简析及PSO算法框架分析
* 针对BPP问题的PSO算法框架套用
  * **速度公式**的修改
  * 引入**蛙跳算法**的**种群分类思想**
  * **Local Search** 思想的延伸
  * **OOP** - 粒子**行为分析及抽象**
* 代码分析和对不同数据量下的程序的执行情况
* 总结

***

## 问题描述

> 二维的多目标装箱问题指的是将一批晓得物品按照一定的顺序和放入的方式放入到集装箱中，目标是是的集装箱的空间利用率最大或者说是让我们的集装箱的放入的物品的数目最多，本人在实践中采用二空间划分的方法来实现

1. 目前已知**一组物品**需要被放进集装箱中，忽略高维的因素，本问题只考虑**二维**的情况
2. 集装箱的大小是有限制并且固定的
3. 物品在放入的过程中存在有**旋转**的情况
4. 物品放入的位置是随意的,只要满足**物品放入的要求和规则**，我们不限制物品的放入位置
5. ​本问题属于 `MAXMIZE` 问题，求解的目标是尽可能的**获取最大的装入物品量**

　$$问题的数学模型建立：$$

​    $Variable:$

​           $agent\ :\ the\ agent\ of\ the\ group$

​               $1.\ now\ :\ the\ sequence\ of\ the\ now$

​               $2.\ nowres\ :\ the\ answer\ of\ the\ sequence\ (now)$

​               $3.\ pbest\ :\ the\ best\ answer\ of\ the\ agent\ in\ the\ history$

​               $4.\ pbestseq\ :\ the\ pbest\ sequence$

​               $5.\ GBEST\ :\ the\ best\ answer\ of\ the\ group\ of\ the\ agent$

​               $6.\ GBESTSEQ\ :\ the\ best\ sequence\ of\ the\ GBEST$

​    $Param : $

​            $1.\ n : the\ number\ of\ the\ goods$

​            $2.\ W\ ,\ H\ : the\ wide\ and\ the\ high\ of\ the\ container$      

​            $3.\ w[\ ]\ ,\ h[\ ]\ :\ the\ wide\ and\ the\ high\ of\ the\ goods$

​            $4.\ Time\ :\ the\ number\ of\ the\ Iterations$

​    $Objective\ function :$

​            $the\ best\ answer\ of\ the\ group\ of\ the\ agent.$

​    $Constraints : $

​            $1.\ Every\ two\ goods\ can\ not\ coincide\ with\ each\ other.$    

​            $2.\ Every\ goods\ can\ not\ overstep\ the\ scope\ of\ the\ container$

> 本问题是一个**NP问题**，采用普通的求法解决将会造成巨大的时间开销，所以我们这里引入随机化的群体智能算法在巨大的解空间中寻求近似最优解，在查阅了相关的论文和资料之后，根据老师上课的讲述的核心内容，采用修改后的粒子群算法PSO来进行实现和优化

***

## 问题分析

> 问题的定义
>
> 1. 问题的输入：
>    * 迭代次数
>    * 种群规模
>    * container的大小
>      * goods的大小
> 2. 问题的输出：
>    * 最优解的大小
>    * 最优解的放入顺序以及放入的旋转的要求

> 二维的集装箱问题是一种典型的组合优化问题，是一个经典的NPC问题，研究该问题对现实生活有很大的参考价值和理论现实的意义，该问题不存在有效时间内的精确解的算法，一般采用启发式的随机化算法来求得近似最优解
>
> 该问题的难点：
>
> *  装箱的顺序，如何合理的设计装箱的过程
> *  解空间的范围过大，除了放入物品的顺序`O(n!)`之外，我们还需要考虑旋转的因素`O(n! * 2^n)`的解空间的大小
> *  虽然幸运的是，已经存在合理的证明，采用`BLF`的装箱设计过程我们的设计出来的顺序的填入是很优秀的，但是要穷举这么大的解空间很不实际

上述的内容就是对问题分析之后的首先得到的问题的几个比较有困难的地方，我将阐述我的想法和相应的对策

1. 解空间过大的搜索方案：

   本文中采用PSO粒子群算法来实现解空间的高效的搜索，之后我会对算法的内容和具体的实现过程进行具体的阐述

2. BLF设计的实现考虑

   我在进行算法的实践过程中，很清楚的注意到了该问题仅次于算法思想的另一个很重要也是很棘手的一个问题 - **如何设计装箱过程**

   李东妮老师上课也给我们提示应用BLF[^Bottom-Left-First]的思路去设计装箱过程，所谓的这个思想就是说我们在放入物品的时候，为了尽可能的充分的利用集装箱的空间，我们将物品有限放在整个集装箱的左下角，并且是先下在左的顺序，作为已经得到了证明的一种优化思路，这里就不在过多的赘语

   但是如何去设计这样的BLF的过程就是我们碰到的和解决的第一个难点，下面我对我的思路进行细致的阐述

   * 对整个装箱的过程和集装箱的装载过程进行抽象和整体考虑之后，我们会发现，我们可以将装箱的**箱体变化**总结在一下的几个方面

     * 因为采用BLF的优化的思路，所以不论我们遇到什么样的情况，我们可以将所有的放入的物品都抽象成是一个在箱体中的一个平台(矩形的货物)

     * 首先先阐明一个坐标系：

       * 我们以箱体的左下角作为原点，以箱体高的方向作为$Y$轴，以箱体的宽的方向作为$X$轴构建坐标系

       * 所有的放入的货物我们也是按照和箱体一样的顺序方向放入(选装的话，方向不变，只是对应方向上的数据发生改变而已)

       * 图示

         ![Figure_1](/home/lantian/File/Study Coding/Optimisation/BPP/Figure_1.png)

     * 这样的一个平台有这么一个参数，这个参数是一个三元组

       $(High\ ,\ Begin\ ,\  End)$

       第一个参数表示平台在箱体坐标系中的平台高度

       第二个参数表示平台在箱体坐标系中的平台的起始的位置

       第三个参数表示平台在箱体坐标系中的平台的结束的位置

     * 每一个平台必须存在于我们的箱体的范围内，初始的平台是我们的箱体的底

     * 每次放入一个物品我们都是选定一个平台作为放置的起始的位置，并且放置是以　$Begin$　的位置对齐来放置的（**保证我们的左优先策略**）

     * 该平台不合适则更换平台来继续匹配操作，知道找到合适的平台或者知道找不到任何一个合适的平台

   * BLF策略的体现

     因为是要超照合适的平台，总存在一种枚举平台的顺序的方案

     所以要实现下左优先的策略，我们这里可以考虑对平台进行相应的排序

     **这里我们采用优先排高度，次优先排起始位置的升序排列的方案**

     按照上述的排序的方案，我们可以发现，我们都是优先的从左下的平台开始进行匹配，这样的话，如果成立就选用，如果不成立就会选取同高度的右边的平台或者上升查找平台从而实现了我们的BLF的思路

   * 平台匹配的情况和平台的变化

     * 平台在匹配的时候，我们关键的操作就是如何判定该物品放在对应的平台上的时候，不会和其他的平台发生**矛盾(重合)**，这一点非常的重要也非常的好实现

       在这里明确出在加到这个平台上的时候，这个矩形货物的左右边界，然后我们枚举所有的剩下的所有的平台，**如果存在其他的平台在这个左右边界之内的话，说明该位置放置当前的货物是不合法的，考虑切换平台**

     * 平台的变化：

       在货物允许放在当前的平台上的时候，我们需要考虑放置之后的两种变化情况

       * 平台被当前放置的矩形完全遮盖，该平台退出平台队列
       * 平台被当前放置的矩形部分覆盖，该平台的 $Begin$ 参数需要调整

   综上，我们就解决了第一个困难的要点 - 如何放置某个顺序和旋转因素的一个货物放入序列

***

## PSO算法简析及PSO算法框架分析

> 粒子群优化算法(Particle swarm optimisation , PSO Algorithm)是由`Kennedy`和`Eberhart`通过从人工生命研究和种群的分析中提取的一种基于群体智能的全局随机搜索算法，PSO因为其需要调整的参数少，算法框架简单，优化效果明显等特点回得了大量的研究和实验
>
> 但是我们还需要认识到，因为PSO算法在后期因为粒子多样性的缺失这一点容易陷入局部最优解，发生过早收敛的问题，所以我们通常不单独的使用粒子群算法，而是将其的思想框架和其他的优秀的随机搜索算法和经验公式结合使用，本例中，我就采用这种扩展的思路实现了PSO算法的扩展，从而获得了相应比较优秀的实验效果

**PSO算法的核心在于如何均衡我们的广度和深度的搜索**

李东妮老师上课从核心本质出发为我们展示了PSO算法高效的原因，稍后我会详细的阐述这点以及基于这一点上的对朴素的PSO算法的改进思路

PSO算法要点：

* 算法的起源：

  * Separation - 分隔：

    种群中的每一个成员（粒子）都存在这逃避拥挤的位置的一个趋势（在算法中体现为保存种群中的粒子的多样性）

  * Alignment - 排列：

    每一个粒子的移动趋势都受到种群的大趋势的影响（在算法中体现在与种群中的例子都要受到群体经验的影响）

  * Cohesion - 聚集：

    每一个种群中的粒子都会受到种群中的其他的粒子的吸引的作用，这里的存在的意义在于保证种群的整体搜索不会出现粒子独立于种群的范围内的情况

  虽然上述的描述中1,3两点是对立的，但是正是有这两种对立的因素的存在才会保障我们的种群的**秩序**和**完整**

* 算法的概念：

  1. 粒子：解空间中的一个确定的当前的解

     粒子需要不断维护两个状态变量

     * 粒子历史最优解
     * 粒子所在种群的历史最优解

  2. 速度：粒子保持上一次的运动的惯性

  3. 影响：

     * 每一个粒子都会受到　**个体经验 + 群体经验**　的综合的影响
     * 影响具体来自这么几个方面：
       1. 粒子的当前的位置
       2. 粒子的速度
       3. 个人历史最优解
       4. 群体历史最优解

     通过上面的影响从而群定粒子的下一个位置

* 算法的框架：

  $P\ =\ Init\_create()\ \ \ \ Create\ the\ group\ of\ the\ agent$

  $Time\ \ -\ \ the\ number\ of\ the\ Iterations$

  $ pbest\ \ -\ \ the\ best\ result\ of\ agent\ in\ the\ history$

  $gbest\ \ -\ \ the\ best\ result\ of\ the\ group\ in\ the\ history$

  ​

  $for\ i\ =\ 1\ to\ Time$

  $\ \ \ \ foreach\ agent\ in\ P$

  $\ \ \ \ \ \ \ \ Fp\ =\ f(agent)$

  $\ \ \ \ \ \ \ \ if\ Fp\ is\ better\ than\ pbest\ :\ Renew\ the\ pbest$

  $\ \ \ \ gbest\ =\ Best(pbest)$

  $\ \ \ \ foreach\ p\ in\ P$

  $\ \ \ \ \ \ \ \ v^{t+1}\ =\ v^t\ +\ c1\ *\ rand\ *\ (pbest\ -\ p)\ +\ c2\ *\ rand\ *\ (gbest\ -\ p)$

  $\ \ \ \ \ \ \ \ p\ =\ p\ +\ v$

  上述的算法框架中，我们可以看到

  * pbest和gbest都是单调的递增函数
  * 其中的最重要的公式在与最后的速度切换公式和粒子位置转换公式
  * c1是个体经验的权重，c2是群体经验的权重，c1,c2的值不做严格要求，但是通常选取 $c1 + c2 = 4$，这样可以保证结果很优秀
  * rand是随机数，正是这个rand保证了我们的算法的优秀的特点和我们的**种群粒子的多样性**

***

## 针对BPP问题的PSO算法框架套用

终于熬了整个问题最关键的一步了，在这里我会详细的阐明以下几点

* 我的处理的思路
* PSO算法的速度公式的改写
* 引入蛙跳算法的种群分类思想
  * 贪心种群
  * 随机种群
* Local Search 的思想的扩展
* 粒子行为分析

1. 针对二维BPP问题的PSO算法处理：

   * 定义粒子：

     粒子是一种特定的货物的装填的排列顺序，每一种货物都有旋转和不旋转两种选择，一个粒子决定了在　$n! * 2^n$　种解的空间中的一种具体的解

   * 定义种群：

     一系列的粒子构成的一个种群，该种群之间的粒子之间存在这高强度的相互的交流

   * 定义速度(定义状态的转移)：

     因为粒子的定义是一种特定的排列顺序，所以这里的速度定义为一个具体的**交换子构成的交换序**

     * 定义交换子和交换序

       不同的粒子之间的解不同导致解的顺序是不同的，这里的定义一个交换自就是两个顺序的位置的互换，交换序就是大量的交换子的集合

     这里抽象的交换序代表了我们的不同的解的差异，亦可以相对的反映出我们的优秀的解和我们的当前的解的差异在哪里，这样的差异我们反而可以理解成是种群对粒子的群体经验

2. 速度公式的改写

   通过上述的PSO的定义我们可以发现一个很奇怪的问题，首先让我们观察一下速度公式：

   $\ \ \ \ \ \ \ \ v^{t+1}\ =\ v^t\ +\ c1\ *\ rand\ *\ (pbest\ -\ p)\ +\ c2\ *\ rand\ *\ (gbest\ -\ p)$

   因为我们的定义的速度是很现实的一种交换序，没有办法用具体的数据去衡量这样的一个**"速度"**的大小,所以这里需要引入李东妮老师上课提到的算法的共同的核心要点，并利用这个要点实现贴合算法框架的速度公式的改写

   * Exploration : 广度的搜索
   * Exploitation : 深度的搜索

   不仅仅是PSO算法，群体智能算法都需要在一定的范围内合理的均衡我们的深度和广度的搜索的情况

   1. 太偏向于广度的搜索会导致我们没有办法搜索到更优秀的解，应接不暇
   2. 太偏向于深度的搜索会导致我们没有办法全面考虑到其他解空间的最优值，陷入局部最优

   所以我们在从这两点出发观察速度公式

   * $v^t$代表我们的广度上的搜索，表现为一种突破种群的束缚，向外搜索的趋势
   * $c1\ *\ rand\ *\ (pbest\ -\ p)\ +\ c2\ *\ rand\ *\ (gbest\ -\ p)$:代表我们在已经搜索过的范围内的深度的挖掘

   经过上述的抽象，我们就可以开始在不改变算法框架的基础上的速度公式的改写

   经过合理的测试，我选择结果比较良好的一种方式如下：

   1. `0.1*n`[^该参数可以调节]次的随机交换，代表我们的广度上的搜索
   2. 后续利用**个体经验**和**群体经验**对比我们的**当前的解**生成的**交换序**进行当前解的交换，代表深度上的搜索

   **$Note:$**这里的0.1的参数是可以根据我们的数据情况进行动态的修改，不过我选择的是0.1作为默认值

3. 引入蛙跳算法的种群分类的思想：

   蛙跳算法的原理中声明了我们的一个大种群是可以存在不同文化和交流强度的小种群的

   在首先说明我的想法之前，我先描述一个我打发现：

   1. 不正确的贪心：

      定义一个该问题的一个贪心的思路：

      我们首先将体积小的货物装入我们的集装箱中，换句话说就是将我们的种群按照货物的面积大小按照递增的顺序进行排序

      不正确的贪心选择性质：

      　　假如存在一个暴力最优解，那么我们通过将这个暴力最优解中的一个物品利用面积比它小的货物去替换，那么显然我们可以会发现我们的代价没有增大(相反，我们的空余的面积增大，使得我们的更有机会或者说概率去存放更多的货物)，但是我们需要明白一点，这个贪心选择性质是错误的，准确的说是一个**必要条件**，我们只能确定只有面积和长和宽都同时小的货物才可一去替换一个现有的在集装箱中的货物的时候才是满足这样的贪心选择性质的，但是实际上很大的概率[^相对于比较扁平的情况]存在这面积小但是长和宽不同时小的情况，但是我们可以从这里面总结出一点

      > 相对来说，按照面积从小到大进行排序有很大可能会得到一个很优秀的解

   2. 但是我们又不可以将我们的所有的目光都局限在我们的**“贪心”**的思路上去，相反的，有可能有些情况下，我们的这样的贪心的思路优化的是非常的低效的(比如说长很长但是宽很短的情况，面积虽然小，但是却将我们的集装箱分割开来降低了我们之后的装入物品的能力)

      所以，我为了弥补贪心这样的缺陷，想到了这样一点

      >上述的贪心低效的情况相对来说并不是很常见（相对来说），所以为了弥补贪心的搜索的盲区，我生成一个大的**随机种群**，**遍布整个解空间**,从而充分的考虑所有的情况


   综上，我对总的粒子群进行了分组

   * 分为**贪心子种群和随机子种群**，两个种群分开独立的各自演化
   * 最后从打的种群中挑选出最优秀的几个粒子在构成一个新的种群
   * 新种群最终演化求得近似最优解

   这样的话，我就充分考虑了很多的情况，实践也证明，这样的思路是非常的高效的，可以帮助我掏出一些固有的局部最优解的情况

   $Note:$这里对两个分开的种群的粒子数目没有明确的要求，不过我是**按照1:5的比例**去构建这两个种群的毕竟贪心的种群中，贪心的思路已经非常的具体了，不需要太多的粒子去考虑太多的情况(**贪心的解空间并不是很大**)

4. Local Search思想的延伸

   在之前的编写模拟退火和其他的Local Search的代码的过程中，我发现了很重要的一点，在实际的搜索过程中，我们其实相当于是在一颗解空间的决策树上进行遍历，无论是模拟退货还是Local Search中，我们都会引入一个概念叫做**决策树上的回溯**,但是相对的来说，我个人认为决策树上的额回溯本质上还是不如决策树上的跳跃来的更高效，我们通过利用随机交换的思想切换决策树上的当前的分支，从而实现决策的跳跃

   >我改写的速度公式中，广度上的搜索是利用随机交换序的方式实现的，在这里引用的就是我们的Local Search的决策跳跃的过程，在一个当前最优的基础上跳跃向一个更优的位置，**实现我们的广度上的有目的的搜索**

5. 从面向角度的出发分析粒子的行为

   1. 粒子的属性：
      * 当前解
      * 当前解的序列
      * 历史最优解
      * 历史最优解的序列
   2. 粒子的行为：
      * 状态的转移
      * 当前解大小的计算

***

## 代码分析和对不同数据量下的程序的执行情况

1. 代码：

   代码用Python编写

   ```python
   #!/usr/bin/python3

   # This module was the MAXMIZE Question.

   from time import *
   from random import *
   from copy import *
   import sys
   from operator import itemgetter    # Just for the sort ( queue )

   INF = 1e20   # Define the inf by myself.

   # All the param read from the function readfile.

   PACK_H = INF   # the high about the pack
   PACK_W = INF   # the weight about the pack
   PACK_AREA = INF# the area of the pack
   CELL_H = []    # the high of every cell
   CELL_W = []    # the weight of every cell
   CELL_AREA = [] # the area of all the cell
   N = INF        # the size of the question.
   TIME = INF     # the number of the iteration about PSO Algorithm.

   class agent:
       def __init__(self , now):
           self.nowseq = now
           self.nowres = 0
           self.pbestseq = deepcopy(self.nowseq)
           self.pbestres = 0
       def move(self,x1,x2,gbest):
           '''
           n - the number od the iterations.
           '''
           times1 = int(x1 * N)
           times2 = int(x2 * N)
           v1 = self.swap_pbest()
           v2 = self.swap_gbest(gbest)
           v2_len = len(v2)
           if len(v2) < times2 : times1 += times2 - v2_len
           t = range(N)
           for i in range(times1):
               k = [sample(t , 2)]
               swap(self , k)
               self.calculate()    # Inner make sure that nowres can be changed!
           swap(self , v1)
           swap(self , v2)
           self.calculate()
       def swap_pbest(self):
           w = []
           for i,j in enumerate(self.pbestseq):
               for xi,xj in enumerate(self.nowseq):
                   if xj[0] == j[0]:
                       if xi != i:w.append([xi , i])
                       break
           return w
       def swap_gbest(self,gbest):
           w = []
           for i ,j in enumerate(gbest):
               for xi,xj in enumerate(self.nowseq):
                   if xj[0] == j[0]:
                       if xi != i : w.append([xi , i])
                       break
           return w
       def calculate(self):
           remaining = PACK_AREA
           count = 0
           queue = [[0 , 0 , PACK_W]]    # the queue of the platform. (high , left , right)
           for i in range(N):
               h , w = CELL_H[self.nowseq[i][0]] , CELL_W[self.nowseq[i][0]]
               if remaining < h * w : continue    # This cell is too big !
               if self.nowseq[i][2] == 1 : h , w = w , h    # Rotation!
               for nu , data in enumerate(queue):    # Begin to choose the platform
                   begin = data[1]
                   end = data[2]
                   high = data[0]
                   #boxleft = (begin , high , high + h)    # Make sure the box left 
                   #boxright = (end , high , high + h)    # Make sure the box right
                   for j in queue:    # Search all the platform 
                       if high < j[0] < high + h and (begin <= j[1] <= begin + w or begin <= j[2] <= begin + w):
                           break    # This platform can not satisfied!
                       if high + h <= PACK_H and begin + w <= PACK_W:pass
                       else :break
                   else :    # This platform is OK!
                       if w >= end - begin :
                           queue.remove(data)    # Dangerous but also OK!
                           queue.append([high + h , begin , begin + w])
                       else : 
                           queue[nu][1] = begin + w
                           queue.append([high + h , begin , begin + w])
                       queue.sort(key = itemgetter(0 , 1))
                       count += 1
                       remaining -= h * w
                       break    # Begin to break when we find the position.
           self.nowres = count    # Renew the result !

   def create_best_group():
       '''
       Create the best group - size 10
       Input:
           Nothing
       Output:
           the list of the best group.

       REMEMBER:
           Important param:
           Alpha > 0.5 : bottom first
                 <= 0.5 : left first
           Beta > 0.5 : rotate (change the w,h)
                <= 0.5 : do not rotate 
       '''
       data = list(enumerate(CELL_AREA))
       p = sorted(data , key = lambda t:t[1])
       res = []    # the answer wait to return
       # ans -----------------------------------
       ans = []    # the first solution 
       for i in range(N):
           w = []
           w.append(p[i][0])
           alpha = random()
           if alpha > 0.5 : w.append(1)
           else : w.append(-1)
           beta = random()
           if beta > 0.5 : w.append(1)
           else : w.append(-1)
           ans.append(w)
       res.append(ans)
       # create the first best (By greedy)-----
       # Create another 9 agent from the first answer! Change four parts!
       for i in range(9):
           k = range(N)
           t = sample(k , 2)
           w = sample(k , 2)
           y = sample(k , 2)
           phy = deepcopy(ans)
           phy[t[0]] , phy[t[1]] = phy[t[1]] , phy[t[0]]
           phy[w[0]] , phy[w[1]] = phy[w[1]] , phy[w[0]]
           phy[y[0]][1] = -phy[y[0]][1]
           phy[y[1]][2] = -phy[y[1]][2]
           res.append(phy)
       return res

   def create_random_group():
       '''
       Create the random group - size 30
       Input:
           Nothing
       Output:
           the list of the random group.
       '''
       data = list(range(N))
       res = []
       for i in range(30):
           shuffle(data)
           ans = []
           for j in range(N):
               w = []
               w.append(data[j])
               alpha = random()
               if alpha > 0.5 : w.append(1)
               else : w.append(-1)
               beta = random()
               if beta > 0.5 : w.append(1)
               else : w.append(-1)
               ans.append(w)
           res.append(ans)
       return res

   def init_agent():
       '''
       Use the function:
           create_best_group
           create_random_group
       to init the agents , which have 40 agents , and first have 10 , second have 30.
       And make sure we have over the sequence with P_BEST AND P_BEST_SEQ
       Input:
           Nothing
       Output:
           the list which present the 40 agent by Tuple.(group two)
           And every agent have its init nowseq and nowres , hisseq and hisres is the 
           same as the nowseq and nowres.
       '''
       P1 = []
       P2 = []
       b1 = create_best_group()
       b2 = create_random_group()
       for i in b1:
           P1.append(agent(i))
           P1[-1].calculate()    # Make sure that we have calculated!
       for j in b2:
           P2.append(agent(j))
           P1[-1].calculate()
       return (P1,P2)

   def swap(data , sl):
       '''
       Use the swap list to swap the agent now seq.
       Input:
           data - the certain agent.
           sl - the swap list we want to use
       Output:
           Nothing.
       Side effect:
           the data maybe changed by our algorithm.
       '''
       for pdata in sl:
           i , j = pdata[0] , pdata[1]
           data.nowseq[i] , data.nowseq[j] = data.nowseq[j] , data.nowseq[i]

   # The PSO_best and The PSO_random have the Iteration times
   # And the times can be changed by myself.
   # Default 100 - 1000.

   # And the Mixup method use the PSO_best to find the better solution 
   # By the param 0.1*n - 0.1*n 

   # The x1 , x2 are the param which belongs to the times of swap and Iteration.

   def PSO(tenbest , x1 , x2 ):
       '''
       This function is aimed at the 10 best .
       So the param may changed .

       In this fucntion changed the 10 best only .
       the param is 0.1*n - 0.2*n

       The most important function in this module.
       Fix the velocity function and hybird with the thinking in the Iteration
       Local Search.
       First use 0.1*n times iteration by random swap to enlarge the space we 
       discovered.
       And use 0.1*n times swap which from (pbest - now) and (gbest - now) , use
       the experience in the group and itself to create rediscovered the space we 
       have thought about but thinking more instead.
       '''
       # The local-global best--------------
       P_BEST = 0
       P_BEST_SEQ = []
       # -----------------------------------
       for i in range(TIME):
           for j in tenbest:
               if j.nowres > j.pbestres:    # If the answer is better ,renew the pbest
                   j.pbestres = j.nowres 
                   j.pbestseq = deepcopy(j.nowseq)
           # renew the gbest
           t = -1
           for a,b in enumerate(tenbest):
               if b.pbestres > P_BEST:
                   t = a
                   P_BEST = b.pbestres
           if t != -1:
               P_BEST_SEQ = deepcopy(tenbest[t].pbestseq)

           # Move the agents.
           for j in tenbest:
               j.move(x1,x2,P_BEST_SEQ)    # Move the agent with the function: swap , swap_pbest , swap_gbest
           if i % (int(0.1 * TIME)) == 0 : print("Procesing %s / %s ..." % (i , TIME) , end = '\r')    # Wonderful printing format.
           
       return (P_BEST , P_BEST_SEQ)

   def readfile():
       # REMEMBER to use global to fix the GLOBAL VARIABLE !
       global CELL_AREA
       global CELL_H
       global CELL_W
       global N
       global TIME
       global PACK_H
       global PACK_W
       global PACK_AREA
       N = int(input())
       TIME = int(input())
       PACK_H = int(input())
       PACK_W = int(input())
       PACK_AREA = PACK_H * PACK_W
       h = input().split()
       w = input().split()
       area = list(range(N))
       for i in range(N):
           h[i] = int(h[i])
           w[i] = int(w[i])
           area[i] = h[i] * w[i]
       CELL_H = h
       CELL_W = w
       CELL_AREA = area
       print("All the param have gotten from the file.")

   def writefile(gb , gbs):
       '''
       This function use ?
       '''
       print('The best solution is :')
       for a,i in enumerate(gbs):
           if a == gb : break    # Only print the result , not all the package!
           sys.stdout.write(str(a + 1) + ' CELL : ')
           if i[2] == 1 : sys.stdout.write(str((CELL_W[i[0]] , CELL_H[i[0]])))
           else :  sys.stdout.write(str((CELL_H[i[0]] , CELL_W[i[0]])))
           print()   
       print("All the solution is the tuple which length is 2 , (0 - Height , 1 - Weight)")
       print('The best answer is : ' + str(gb))

   def choose(T):
       T.sort(reverse=True , key = lambda p:p.pbestres)
       return T[:10]

   if __name__ == "__main__":
       t1 = time()
       readfile()   # Get the cell param in this function.

       bestg , randomg = init_agent()   # This function get two group sequence.
       print("Create the init agents successfully!")
       
       PSO(bestg , 0.1 , 0.2)
       print("PSO in 10 best agents Over!")
       PSO(randomg , 0.4 , 0.1)
       print("PSO in 30 random agents Over!")

       bestg.extend(randomg)    # Combine two group.
       ans = choose(bestg)    # this function choose 10 top agent.
       print("PSO in the end Over!\nGet ready to Ouput the Optimisation result!")
       
       gb , gbs = PSO(ans , 0.1 , 0.1)    # this function use the PSO_best function to create the best solution from the solutions we have now.

       writefile(gb , gbs)   # this fucntion print the answer formatly.
       t2 = time()
       w = int((t2 - t1)*100) / 100.0
       print("Time using : " + str(w) +'s')
   ```

2. 数据表现：

   相关的数据资料和结果文件保存在文件中

***

## 总结

* 通过这次的算法的实践，体会到了实际当中，群体智能算法只是一套具体的算法框架，要是落实到具体的问题上，我们还需要对算法的框架的细节做整体的调整
* 对于这类NPC问题，我们的群体智能算法只要生成了符合预期的结果，相应的时间代价只要不过分就可以忽略[^可容忍]
* 群体智能算法中隐含有非常鲜明的**并行计算**的成分
* 为了解决局部最有的问题，我们偶尔需要将群体智能算法和其他的算法或者思想相结合
