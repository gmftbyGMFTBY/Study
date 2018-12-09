#!/usr/bin/python3

from numpy import *

def loaddataset(filename):
    '''
    该函数用来加载对应的数据到内存
    '''
    datamat = []
    f = open(filename)
    for i in f.readlines():
        cur = i.strip().spilt('\t')
        cur = map(float , cur)
        datamat.append(cur)
    return datamat

def binsplitdataset(dataset , feature , value):
    '''
    该模块用来二元切分我们的数据集
    '''
    mat0 = dataset[nonzero(dataset[:,feature] > value)[0] , :]
    mat1 = dataset[nonzero(dataset[:,feature] <= value)[0] , :]
    return mat0 , mat1

def createtree(dataset , leaftype = createleaf , errtype = calerr , ops = (1,4)):
    '''
    创建树的函数
    leaftype : 给出创建叶节点的函数
    errtype : 代表计算误差的函数
    ops : 创建树的其他参数元组
    '''
    feat , val = choosebestsplit(dataset , leaftype , errtype , ops)
    if feat == None : return val
    tree = {}
    tree['splitfeat'] = feat    # 分割的特征
    tree['splitecalue'] = val    # 分割的特征值
    lset , rset = binsplitdataset(dataset , feat , val)
    tree['left'] = createtree(lset , leaftype , errtype , ops)
    tree['right'] = createtree(rset , leaftype , errtype , ops)
    return tree

# 接下来定义相应的构架叶子节点的函数和计算方差的函数和最佳切分函数
def createleaf(dataset):
    '''
    该函数用来生成叶节点
    当我们的切分函数不在及逆行切分的时候，我们调用该函数够构建叶节点的模型，在回归树中该叶节点的模型就是一个均值
    '''
    return mean(dataset[:, -1])    # 对目标变量的均值计算

def calerr(dataset):
    '''
    该函数是计算误差的估计函数，计算当前的样本的平方误差
    '''
    return var(dataset[:,-1] * shape(dataset)[0])   # var是均方差

def choosebestsplit(dataset , leaftype = createleaf , errtype = calerr , ops = (1,4)):
    '''
    该函数用来说寻找最佳切分的特征和最佳切分的特征值
    ops参数用来用户制定停止的时机 ops = (tols , toln)
        tols : 容许的误差下降值
        toln : 切分的最小样本数
    '''
    tols = ops[0]
    toln = ops[1]
    if len(set(dataset[:,-1].T.tolist()[0])) == 1:
        # 如果样本中的所有值都是相同的，退出
        return None , leaftype(dataset)
    m , n = shape(dataset)    # 数据集的规模
    s = errtype(dataset)    # 计算当前的样本的总误差
    # 初始化
    besterr = inf
    bestindex = 0
    bestvalue = 0
    for i in range(n-1):
        # 枚举所有的特征
        for j in set(dataset[:,i]):
            # 枚举该特征的所有的特征值
            # 二元切分
            mat0 , mat1 = binsplitdataset(dataset , i , j)
            if shape(mat0)[0] < toln or shape(mat1)[0] < toln : 
                # 如果切分得到的数据集的结果不满足用户设定的要求，不切分
                continue
            newerr = errtype(mat0) + errtype(mat1)
            if newerr < besterr:
                besterr = newerr
                bestindex = i
                bestvalue = j
    if s - bests < tols:
        # 如果误差的降低没有满足要求，放弃
        return None , leaftype(dataset)
    mat0 , mat1 = binsplitdataset(dataset , bestindex , bestvalue)    # 最佳二元切分
    if shape(mat0)[0] < toln or shape(mat1)[0] < toln :
        # 如果切分的结果很小，放弃切分
        return None , leaftype(dataset)
    return bestindex , bestvalue

if __name__ == "__main__":
    test = mat(eye(4))
    a , b = binsplitdataset(test , 1 , 0.5)
    print(test)
    print(a)
    print(b)
