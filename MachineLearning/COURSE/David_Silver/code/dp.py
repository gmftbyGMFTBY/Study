#!/usr/bin/python3

'''
方格世界的动态规划代码演示

    0  1  2  3 
    4  5  6  7
    8  9  10 11
    12 13 14 15

状态空间: 1 ~ 14 普通状态，0, 15 是终止状态
动作空间: 上下左右
转移概率: 100% 转移到策对应的方向
即时奖励: 落入非终止状态-1，终止状态为0
衰减系数: 1
初始策略随机的走向其他的4个方向
'''

states = [i for i in range(16)]
values = [0 for _ in range(16)]
actions = ['n', 'e', 's', 'w']
ds_actions = {'n': -4, 'e': 1, 's': 4, 'w': -1}
policy = [0 for _ in range(16)]    # policy, default means 0.25 for all the directions
gamma = 1.0

def nextstate(s, a):
    next_state = s
    if (s % 4 == 0 and a == "w") or (s < 4 and a == "n") or \
       ((s + 1) % 4 == 0 and a == "e") or (s > 11 and a == "s"):
        pass
    else:
        ds = ds_actions[a]
        next_state = s + ds
    return next_state

def rewardof(s):
    return 0 if s in [0, 15] else -1

def isterminal(s):
    return s in [0, 15]

def getsuccessors(s):
    successors = []
    if isterminal(s):
        return successors
    for a in actions:
        next_state = nextstate(s, a)
        # if s != next_state:
        successors.append(next_state)
    return successors

def updatevalue_v(s):
    # value iteration update
    sucessors = getsuccessors(s)
    newValue = 0
    num = 4                         # len(successors)
    valuealter=[]
    reward = rewardof(s)
    for next_state in sucessors:
        value_tem = reward + gamma * values[next_state]    # probability is 1 for the next state
        valuealter.append(value_tem)
        newValue = max(valuealter) if valuealter else 0
    return newValue

def updatevalue(s):
    # policy iteration update
    sucessors = getsuccessors(s)
    if not sucessors: 
        return 0

    newvalue = -4                   # values[s]
    num = 4                         # len(successors)
    reward = rewardof(s)
    for next_state in sucessors:
        # the realpolicy iteration
        key = reward + gamma * values[next_state]
        if key > newvalue: 
            newvalue = key
        # newvalue += 1.00 / num * (reward + gamma * values[next_state])
    return newvalue

def performoneiteration():
    newvalues = [0 for _ in range(16)]
    for s in states:
        newvalues[s] = updatevalue(s)
        # newvalues[s] = updatevalue_v(s)
    global values
    # over the value evaluation
    values = newvalues
    printvalue(values)

def printvalue(v):
    for i in range(16):
        print('{0:>6.2f}'.format(v[i]),end = " ")
        if (i + 1) % 4 == 0:
            print("")
    print()

def main():
    max_iterate_times = 10
    cur_iterate_times = 0
    while cur_iterate_times <= max_iterate_times:
        print("Iterate No.{0}".format(cur_iterate_times))
        performoneiteration()
        cur_iterate_times += 1
    printvalue(values)

if __name__ == "__main__":
    main()
