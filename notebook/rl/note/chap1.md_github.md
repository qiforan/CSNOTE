# Reinforcement Learning 笔记

## 马尔科夫决策

### 马尔科夫过程

1. 在一个时序过程中，如果  ![math](https://render.githubusercontent.com/render/math?math=t%2B1)  时刻的状态仅取决于  ![math](https://render.githubusercontent.com/render/math?math=t)  时刻的状态  ![math](https://render.githubusercontent.com/render/math?math=S_%7Bt%7D)  而与  ![math](https://render.githubusercontent.com/render/math?math=t)  时刻之前的状态都无关的话，则认为  ![math](https://render.githubusercontent.com/render/math?math=t)  时刻的状态  ![math](https://render.githubusercontent.com/render/math?math=S_t) 具有**马尔科夫性**

2. 如果过程中每个状态都具有马尔科夫性，则这个**过程**具有马尔科夫性

3. 具备了马尔科夫性的随机过程称为**马尔科夫过程**，又称**马尔科夫链**。

描述一个马尔科夫过程的核心是状态转移概率矩阵:


![math](https://render.githubusercontent.com/render/math?math=P_%7Bss%27%7D%20%3D%20%5Cmathbb%7BP%7D%5BS_%7Bt%2B1%7D%3Ds%27%7CS_t%20%3D%20s%5D)



### 马尔科夫奖励过程

如果把奖励考虑进马尔科夫过程，则为**马尔科夫奖励过程**，即元组  ![math](https://render.githubusercontent.com/render/math?math=%5Clangle%20S%2C%20P%2C%20R%2C%20%5Cgamma%20%5Crangle) 

* S是一个有限状态集

* P是状态转移概率矩阵

* R是奖励函数:  ![math](https://render.githubusercontent.com/render/math?math=R_s%20%3D%20%5Cmathbb%7BE%7D%5BR_%7Bt%2B1%7D%7CS_t%3Ds%5D) 

*  ![math](https://render.githubusercontent.com/render/math?math=%5Cgamma)  是折扣因子:  ![math](https://render.githubusercontent.com/render/math?math=%5Cgamma%20%5Cin%20%5B0%2C1%5D) 

**奖励**是 agent 到达某个状态，环境给予的反馈。

**收获**是一个马尔科夫奖励过程中从某一个状态 ![math](https://render.githubusercontent.com/render/math?math=S_t) 开始到终结状态时所有奖励的有衰减和。数学表达如下:


![math](https://render.githubusercontent.com/render/math?math=G_t%20%3D%20R_%7Bt%2B1%7D%20%2B%20%5Cgamma%20R_%7Bt%2B2%7D%20%2B%20%5Cldots%20%3D%20%5Csum_%7Bk%3D0%7D%5E%7B%5Cinfty%7D%7B%5Cgamma%7D%5EkR_%7Bt%2Bk%2B1%7D)



**价值**是马尔科夫奖励过程中的期望。数学表达式为:


![math](https://render.githubusercontent.com/render/math?math=v%28s%29%20%3D%20%5Cmathbb%7BE%7D%5BG_t%7CS_t%3Ds%5D)



* 一个状态的价值是该状态的收获的期望，也即从该状态开始依据状态转移概率矩阵采样生成一系列的状态序列，对每个状态序列计算该状态的收获，然后计算平均。

* 采样越多，该平均收获就越接近其价值。

* 价值可以反应某个状态的重要性。

**价值函数**建立了状态到价值的映射，对价值函数进行展开:


![math](https://render.githubusercontent.com/render/math?math=%5Cbegin%7Baligned%7D%0Av%28s%29%26%3D%5Cmathbb%7BE%7D%5BG_t%7CS_t%3Ds%5D%20%5C%5C%0A%26%3D%5Cmathbb%7BE%7D%5BR_%7Bt%2B1%7D%20%2B%20%5Cgamma%20R_%7Bt%2B2%7D%2B%7B%5Cgamma%7D%5E2R_%7Bt%2B3%7D%2B%20%5Cldots%20%7C%20S_t%3Ds%5D%20%5C%5C%0A%26%3D%5Cmathbb%7BE%7D%5BR_%7Bt%2B1%7D%20%2B%20%5Cgamma%20%28R_%7Bt%2B2%7D%20%2B%20%5Cgamma%20R_%7Bt%2B3%7D%20%2B%20%5Cldots%20%29%20%7C%20S_t%20%3D%20s%5D%20%5C%5C%0A%26%3D%5Cmathbb%7BE%7D%5BR_%7Bt%2B1%7D%20%2B%20%5Cgamma%20G_%7Bt%2B1%7D%20%7C%20S_t%3Ds%5D%20%5C%5C%0A%26%3D%5Cmathbb%7BE%7D%5BR_%7Bt%2B1%7D%20%2B%20%5Cgamma%20v%28S_%7Bt%2B1%7D%29%7CS_t%3Ds%5D%0A%5Cend%7Baligned%7D)



如果用  ![math](https://render.githubusercontent.com/render/math?math=s%27)  表示下一时刻任一可能状态，则上述方程可以写为:


![math](https://render.githubusercontent.com/render/math?math=v%28s%29%20%3D%20R_s%20%2B%20%5Cgamma%20%5Csum_%7Bs%27%20%5Cin%20S%7D%20P_%7Bss%27%7Dv%28s%27%29)


即为**贝尔曼方程(Bellman equation)**,提示一个状态的价值由该状态的奖励及后续状态价值按概率分布求和以一定的衰减比例联合组成。

也可以写成如下矩阵形式：


![math](https://render.githubusercontent.com/render/math?math=v%20%3D%20R%20%2B%20%5Cgamma%20Pv)


理论上可以直接求解，即


![math](https://render.githubusercontent.com/render/math?math=v%3D%281-%5Cgamma%20P%29%5E%7B-1%7DR)


时间复杂度是 ![math](https://render.githubusercontent.com/render/math?math=O%28n%5E3%29) ，但转移矩阵  ![math](https://render.githubusercontent.com/render/math?math=P)  一般都是未知的。

### 马尔科夫决策过程

**马尔科夫决策过程(Markov decision process, MDP)** 是由  ![math](https://render.githubusercontent.com/render/math?math=%5Clangle%20S%2C%20A%2C%20P%2C%20R%2C%20%5Cgamma%20%5Crangle)  组成，其中

* S是一个有限状态集

* A是一个有限动作集

* P是集合中基于行为的状态转移概率矩阵:  ![math](https://render.githubusercontent.com/render/math?math=P_%7Bss%27%7D%5Ea%20%3D%20%5Cmathbb%7BE%7D%5BS_%7Bt%2B1%7D%3Ds%27%7CS_t%3Ds%2C%20A_t%3Da%5D) 

* R是奖励函数:  ![math](https://render.githubusercontent.com/render/math?math=R_s%20%3D%20%5Cmathbb%7BE%7D%5BR_%7Bt%2B1%7D%5Ea%7CS_t%3Ds%2C%20A_t%20%3D%20a%5D) 

*  ![math](https://render.githubusercontent.com/render/math?math=%5Cgamma)  是衰减因子:  ![math](https://render.githubusercontent.com/render/math?math=%5Cgamma%20%5Cin%20%5B0%2C1%5D) 

个体状态下从行为集中选择一个一个的依据称为**策略(policy)**,用字母  ![math](https://render.githubusercontent.com/render/math?math=%5Cpi)  表示。策略  ![math](https://render.githubusercontent.com/render/math?math=%5Cpi)  是某一状态下基于行为集合的一个概率分布:


![math](https://render.githubusercontent.com/render/math?math=%5Cpi%28a%7Cs%29%20%3D%20%5Cmathbb%7BP%7D%5BA_t%20%3D%20a%20%7C%20S_t%20%3D%20s%5D)


当给定一个马尔科夫决策过程   ![math](https://render.githubusercontent.com/render/math?math=M%20%3D%20%5Clangle%20S%2C%20A%2C%20P%2C%20R%2C%20%5Cgamma%20%5Crangle)  和策略  ![math](https://render.githubusercontent.com/render/math?math=%5Cpi) , 那么有状态和奖励序列  ![math](https://render.githubusercontent.com/render/math?math=S_1%2C%20R_2%2C%20S_2%2C%20R_3%2C%20S_3%2C%20%5Cldots)  ， 有以下两个方程: 


![math](https://render.githubusercontent.com/render/math?math=%5Cbegin%7Baligned%7DP_%7Bss%27%7D%5E%7B%5Cpi%7D%26%3D%20%5Csum_%7Ba%20%5Cin%20A%20%7D%20%5Cpi%20%28a%7Cs%29%20P_%7Bss%27%7D%5Ea%20%5C%5C%0AR_S%5E%7B%5Cpi%7D%20%26%3D%20%5Csum_%7Ba%20%5Cin%20A%7D%20%5Cpi%28a%7Cs%29%20R_s%5Ea%0A%5Cend%7Baligned%7D)


