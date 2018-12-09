1. Q leanring 是一种决策过程，Q表
    状态和动作的二维表

2. Algorithm
    Init Q(S, A) randomly
    Repeat for each episode

    ```
    init s
    Repeat for each step of episode
        Choose a of s using policy derived from Q (greedy or something)
        Take action a, observe r, get new status s'
        Q(s, a) = Q(s, a) + \alpha * [r + \gamma * max(Q(s', a') - Q(s, a))]
        s = s'
    until s is terminal status
    ```

    1. $$\epsilon$$ -greedy is a policy to get the good action a
    2. $$\alpha$$ decide how much need to fix, low than or equal 1
    3. $$\gamma$$ is a decay weight, g means $$\gamma$$
        Q(s1) = r2 + g Q(s2) = ... = r2 + g r3 + g^2 r4 + ...


---

1. Q-Learning 中重要的概念是状态和行为，分别对应有向图中的节点和弧，其中记录信息的Q表中状态为行，行为为列，类似的也可以构建一个reward矩阵，同样状态为行，行为为列记录环境中的奖惩信息

2. 转移规则
   $$
   Q(s,a)=R(s,a) + \gamma \cdot \max_{a'}\{Q(s',a')\}
   $$

   * $$s, a$$: 当前的状态和行为
   * $$s',a'$$: 下一个状态和下一个行为
   * $$0\leq\gamma<1$$: 学习参数，控制对未来奖励的重视程度
   * $$R(s,a)$$: 在状态 $$s$$ 下采取 $$a$$ 动作的立即奖励，取自 reward 矩阵

3. Q-Learning Algorithm

   1. 给定参数 $$\gamma$$ 和 reward 矩阵 $$R$$
   2. $$Q=0$$
   3. 对每一个 episode
      1. 随机选取开始状态 $$s$$
      2. 没有到达终止状态
         1. 采用某种策略选取行为 $$a$$ ($$\epsilon-greedy$$)
         2. 获得下一个状态 $$s'$$
         3. $$Q(s,a)=R(s,a) + \gamma \cdot \max_{a'}\{Q(s',a')\}$$
         4. $$s=s'$$

4. 算法迭代测试阅读，训练效果越好，Q表优化的越好

5. 训练结束，应用算法

   1. $$s=s_0$$
   2. $$a = \max_{a}\{Q(s,a)\}$$
   3. $$s=s'$$
   4. until to terminate