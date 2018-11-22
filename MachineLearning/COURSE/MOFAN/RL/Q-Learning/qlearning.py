#!/usr/bin/python3

'''
easy script for Q learning
'''

import numpy as np
import pandas as pd
import time, pprint

# set the fake random seed
np.random.seed(2)

n_state = 6
actions = ['left', 'right']
epsilon = 0.9
alpha   = 0.1
lam     = 0.9
max_episodes = 100
fresh_time   = 0.01   # time for action, for showing the performance better

def build_q_table(n_state, actions):
    table = pd.DataFrame(
            np.zeros((n_state, len(actions))),
            columns=actions,
    )
    print(table)
    return table

def choose_action(state, q_table):
    state_action = q_table.iloc[state, :]
    if (np.random.uniform() > epsilon) or (state_action.all() == 0):
        action_name = np.random.choice(actions)
    else:
        action_name = state_action.argmax()
    return action_name

def get_env_feedback(s, a):
    # treasure on the right, so left will never get the treasure
    if a == 'right':
        if s == n_state - 2:
            s = 'terminal'
            r = 1
        else:
            s = s + 1
            r = 0 
    else:
        r = 0
        if s == 0:
            s = s
        else:
            s = s - 1
    return s, r

def update_env(s, episode, step_counter):
    env_list = ['-'] * (n_state - 1) + ['T']
    if s == 'terminal':
        interaction = f'Episode: {episode + 1}, total: {step_counter}'
        print('\r' + interaction, end='')
        print('\r' + ' ' * 30, end='')
    else:
        env_list[s] = 'o'
        interaction = ''.join(env_list)
        print('\r' + interaction, end='')
        time.sleep(fresh_time)

def mainloop():
    q_table = build_q_table(n_state, actions)
    for episode in range(max_episodes):
        step_counter = 0
        s = 0
        is_terminal = False
        update_env(s, episode, step_counter)

        while not is_terminal:
            a = choose_action(s, q_table)
            s_, r = get_env_feedback(s, a)
            q_predict = q_table.ix[s, a]
            if s_ != 'terminal':
                q_target = r + lam * q_table.iloc[s_, :].max()
            else:
                q_target = r
                is_terminal = True

            q_table.ix[s, a] += alpha * (q_target - q_predict)
            s = s_

            update_env(s, episode, step_counter + 1)
            step_counter += 1
    return q_table

if __name__ == "__main__":
    q_table = mainloop()
    print(q_table)
