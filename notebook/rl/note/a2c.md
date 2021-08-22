# Advance Actor Critic Algorithm

策略梯度方法使用**神经网络**来学习动作策略(action policy)，比如在 DQN 中，用神经网络逼近 Q value. 在基于 Monte-Carlo 的策略梯度算法中，一个问题就是偏差过大( high variance)。这个问题可以通 **baselining** 来解决。

## 算法细节

"Advantage Actor" 指的是特定动作 $a_t$ 相对 特定状态  $s_t$ 的优势估计，即

$$A(s_t,a_t)=Q(s_t,a_t) - V(s_t)$$

其中 $Q(s_t,a_t)$ 值表示在 $s_t$ 下采取 $a_t$ 后的期望累计奖励(expected future rewards)， $V(s_t)$ 值表示 agent 在 $s_t$ 下采取特定策略  $\pi$ 的期望累计奖励，即

$$V^{\pi}(s) = \mathbb{E}[\sum_{i=1}^{T}\gamma^{i-1}r_i]$$

优势是 $Q(s_t,a_t)$ 相对 $V(s_t)$ 而言，这有点像给 $Q(s_t,a_t)$ 加了一个类似正则的操作。

在 PG-based 算法里，神经网络计算给定状态下每个动作的最佳概率分布，而在 Q-based 算法里，神经网络对每个状态的 Q value 进行估计。显而易见，前者可以通过神经网络计算出最佳动作，后者通常使用 epsilon-greedy 策略，选择最大 Q value 的动作。

策略梯度算法损失函数的梯度如下：

$$\nabla{J(\theta)} \sim \left(\sum_{t=0}^{T-1}\log{P_{\pi_{\theta}}(a_t|s_t)}\right)\left(\sum_{t'=t+1}^T{\gamma^{t'-t-1}r_{t'}}\right)$$


$$G_t = \left(\sum_{t'=t+1}^T{\gamma^{t'-t-1}r_{t'}}\right)$$

其中 $G_t$ 表示状态 $s_t$ 的累计折扣奖励，即 $V^{\pi}(s)$ 的无偏估计。但 PG 算法只能使用每幕完整的数据，因此有很大的偏差，使得训练慢和不稳定。替换 $G_t$ 为优势函数是一个好的选择。

## A2C 算法

A2C 算法的损失函数梯度如下，

$$\nabla{J(\theta)} \sim \left(\sum_{t=0}^{T-1}\log{P_{\pi_{\theta}}(a_t|s_t)}\right)A(s_t,a_t)$$

使用 Bellman 方程，Q value 可以使用 value function 和 reward 表示

$$Q(s_t,a_t) = \mathbb{E}\left[r_{t+1} + \gamma V(s_t) \right]$$

一般我们设置两个网络，一个用来拟合 $\pi_{\theta}$, 一个用来拟合 value function.

此处我们设置一个网络有两部分输出，分别输出 value function 和 policy，类似于 Dueling Q network.

## 损失函数

损失函数可分为 3 部分，每部分都可设置权重。

### 1. Critic loss

$V^{\pi}(s)$ 是期望累计折扣奖励的估计，应该和实际取样得到的累计折扣奖励比较。我们使用均方误差函数作为折现奖励和预测值之间的损失函数 $((V(s)-DR)^2)$.

假设我们收集到一组数据，

$$\left( (V(s_0),r_0),(V(s_1),r_1),(V(s_2),r_2) \right)$$

则 Critic loss 如下，

$$MSE\left( V(s_0), r_0 + \gamma r_1 + \gamma ^2 r_2 + \gamma ^ 3 V(s_3) \right)$$

用 $V(s_3)$ 来替换所需要的 $r_3,r_4, \ldots,r_n$，这种方法被称为自举(bootstrapping).

### 2. Actor loss

使用 The Actor loss 来训练 Actor（即实际策略 $\pi_{\theta}$），即

$$\nabla{J(\theta)} \sim \left(\sum_{t=0}^{T-1}\log{P_{\pi_{\theta}}(a_t|s_t)}\right)A(s_t,a_t)$$

优势函数很容易计算。对于 $\log{P_{\pi_{\theta}}}(a_t|s_t)$ 部分，计算经过 softmax 处理后的 action 概率

### 3. Entropy loss

交叉熵用来测量随机性，entropy 越高，随机性越强。通过添加一个交叉熵损失，增加探索性。