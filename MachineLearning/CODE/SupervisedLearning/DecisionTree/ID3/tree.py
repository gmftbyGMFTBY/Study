#!/usr/bin/python3

from math import log
import operator
import pickle

def storetree(tree , filname):
    f = open(filename , 'w')
    pickle.dump(tree , f)
    f.close()

def gettree(filename):
    f = open(filename)
    return pickle.load(f)

def choosefeature(featurelist):
    '''
    This function return the best choosen for the leather of the decision tree
    Input :
        featurelist : a list of the feature 
    Output :
        int number : a number represents the index of the feature we choose
    Side affect :
        None
    '''
    featuredic = {}
    for i in featurelist:
        if i not in featuredic.keys():
            featuredic[i] = 0
        featuredic[i] += 1
    ans = sorted(featuredic.items() , key = operator.itemgetter(1) , reverse= True)
    return ans[0][0]

def calShannoneEnt(dataset):
    '''
    This function calculate the shannon entropy for the dataset
    Input :
        dataset : a set of data wait to analyse
    Output :
        float number represents the shannonEnt for the dataset
    Side affect :
        None
    Algorithm : 
        1. p(x) : num(x) / num_sum
        2. shannonEnt = - sum(i = 1 , n) p(i) * log(2 , p(i))
    '''
    length = len(dataset)
    label = {}
    for i in dataset:
        currentlabel = i[-1]
        if currentlabel not in label.keys():
            label[currentlabel] = 0
        label[currentlabel] += 1
    shannonEnt = 0.0
    for key in label:
        p = float(label[key]) / length
        shannonEnt -= p * log(p , 2)
    return shannonEnt

def splitDataset(dataset , axis , value):
    '''
    This function splite the dataset with the assured argument axis (the indec of the feature) and the value of this feature in one time
    Input :
        1. dataset : a set of data wait to analyse
        2. axis : the index of the feature
        3. value : the value of this feature 
    Output :
        new_dataset : the sub set of the dataset which only have the feature = value data
    Side affect :
        None
    '''
    new_dataset = []
    for i in dataset:
        if i[axis] == value:
            reducelist = i[:axis]
            reducelist.extend(i[axis+1 :])
            new_dataset.append(reducelist)
    return new_dataset

def choosebestfeature(dataset):
    '''
    This function choose the best feature for the dataset right now
    Input :
        dataset : a set of the data , wait to split into some sub_datasets
    Output :
        int number : the best feature for the dataset , the index of the feature
    Side affext :
        None
    '''
    numfeatures = len(dataset[0]) - 1
    baseentroy = calShannoneEnt(dataset)
    baseinfogain = 0
    basefeature = -1
    for i in range(numfeatures):
        featureset = set([x[i] for x in dataset])
        new_entroy = 0.0
        for value in featureset:
            subdataset = splitDataset(dataset , i , value)
            p = len(subdataset) / float(len(dataset))
            new_entroy += p * calShannoneEnt(subdataset)
        infogain = baseentroy - new_entroy
        if infogain > baseinfogain : 
            baseinfogain = infogain
            basefeature = i
    return basefeature

def createtree(dataset , labels):
    '''
    This function create the decision tree in dict
    Input :
        1. dataset : a set of the data
        2. labels : a list of the labels in the dataset , the name of the features
    Output :
        a multipul dict represents the decision tree.
    Side affect :
        None
    '''
    classlist = [example[-1] for example in dataset]
    if classlist.count(classlist[0]) == len(classlist):
        return classlist[0]
    if len(dataset[0]) == 1:
        return choosefeature(classlist)
    best = choosebestfeature(dataset)
    bestlabel = labels[best]
    tree = {bestlabel : {}}
    del labels[best]
    ans = set([i[best] for i in dataset])
    for i in ans:
        sublabels = labels[:]
        tree[bestlabel][i] = createtree(splitDataset(dataset , best , i) , sublabels)
    return tree

def classify(inputtree , featurelabels , testvac):
    firststr = list(inputtree.keys())[0]
    seconddict = inputtree[firststr]
    featureindex = featurelabels.index(firststr)
    for key in seconddict.keys():
        if testvac[featureindex] == key:
            if type(seconddict[key]).__name__ == 'dict':
                classlabel = classify(seconddict[key] ,featurelabels , testvac)
            else : 
                classlabel = seconddict[key]
    return classlabel


# the test dataset and the labels
mydata = [[1,1,'y'],[1,1,'y'],[1,0,'n'],[0,1,'n'],[0,1,'n']]
labels = ['no surfacng' , 'no flippers']

# print(calShannoneEnt(mydata))

