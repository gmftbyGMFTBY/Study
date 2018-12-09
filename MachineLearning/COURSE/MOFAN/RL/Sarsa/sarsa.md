## Sarsa

---

1. 使用 Q 表，实际中选用 Q 表中值较大的部分进行行动

2. 和 Q-Learning 的更新方式不同

   * 在 Q-Learning 中，我们会观察估计之后会得到的最大的奖励
   * Sarsa 和 Q-Learning 不同，估计观察的行动就会成为下一次的行动

3. 算法 on-policy

   Q-Learning 是 off-policy 的算法，可以离线学习

   ```python
   init Q table
   repeat for each episode
   	init s
       choose a from s using policy derived from Q (\epsilon-greedy)
       repeat for each step of episode
       	take action a, observe r, s'
           choose a' from s' using policy derived from Q (\epsilon-greedy)
           Q(s, a) += \alpha [r + \gamma Q(s', a') - Q(s, a)]
           s = s'
           a = a'
       until s is terminal
   ```

   sarsa 算法相对比较保守

## Sarsa($\lambda$)

---

1. 提速算法，Sarsa 是一种单步更新算法也可以叫 Sarsa(0)，回合更新 Sarsa(1) 是回合的轮数，Sarsa($$\lambda$$) 衰减更新

2. 单步更新: 只有离目标最近的状态会被更新，更新目标点的上一步，之前的状态并没有更新和到达目的地没有很大关系

3. 回合更新: 全局考虑，全局更新，但是需要考虑对冗余重复状态步数的检查

4. $$\lambda$$ 是一个衰减值，结合上述优点，更新离目标近的很大，其他也更新但是具有衰减

5. 算法

   ![](./sarsa-lambda.png)

   ​

   ​