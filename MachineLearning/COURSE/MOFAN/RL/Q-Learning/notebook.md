1. 强化学习具有分数导向性,在环境中不断尝试，尽可能的选择高分行为
2. 算法分类
    * 价值决定行为
        * Q learning
        * Sarsa
        * DQN
    * 直接选择行为
        * Policy Gradients
    * 想象环境
        * Model Based RL

3. 强化学习算法汇总
    * 不理解环境 Model-Free RL
        agent 等待真实环境的反馈
        * Q learning
        * Sarsa
        * Policy Gradients
    * 理解环境 Model-Based RL
        想象不同的反馈，根据经验，理解真实的环境，建立现实环境的模拟
        * Q learning
        * Sarsa
        * Policy Gradients

    * 基于概率
        不同的行为的选择概率不同
        Policy Gradients
    * 基于价值
        对不同的价值打分，选择价值最高行为
        Q learning
        Sarsa
    Actor-Critic: Actor 给出动作，Critic 给出价值

    * 回合更新
        Traditional Policy Gradient
        Monte-Carlo Learning
    * 单步更新: 更有效率
        Q learning
        Sarsa
        Improved Policy Gradients

    * 在线学习
        当前agent边实践边学习
        Sarsa
        Sarsa(lambda)
    * 离线学习
        通过其他agent的经验完善自己
        Q learning
        DQN

4. Why RL: RL with NN is a great way
