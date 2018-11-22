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
        queue = [[0 , 0 , PACK_W , 1]]    # the queue of the platform. (high , left , right , USING(TOP) / 0(BOTTOM))
        for i in range(N):
            h , w = CELL_H[self.nowseq[i][0]] , CELL_W[self.nowseq[i][0]]
            if remaining < h * w : continue    # This cell is too big !
            if self.nowseq[i][2] == 1 : h , w = w , h    # Rotation!
            for nu , data in enumerate(queue):    # Begin to choose the platform
                if data[3] == 0 : continue    # Ignore the bottom platform.
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
                        queue.append([high + h , begin , begin + w , 1])
                        queue.append([high , begin , begin + w , 0])
                    else : 
                        queue[nu][1] = begin + w
                        queue.append([high + h , begin , begin + w , 1])
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
