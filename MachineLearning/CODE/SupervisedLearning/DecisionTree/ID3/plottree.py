'''
Created on Oct 14, 2010

@author: Peter Harrington
'''
import matplotlib.pyplot as plt

decisionNode = dict(boxstyle="sawtooth", fc="0.8")
leafNode = dict(boxstyle="round4", fc="0.8")
arrow_args = dict(arrowstyle="<-")

def getNumLeafs(myTree):
    numLeafs = 0
    firstStr = list(myTree.keys())[0]
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        if type(secondDict[key]).__name__=='dict':#test to see if the nodes are dictonaires, if not they are leaf nodes
            numLeafs += getNumLeafs(secondDict[key])
        else:   numLeafs +=1
    return numLeafs

def getTreeDepth(myTree):
    maxDepth = 0
    firstStr = list(myTree.keys())[0]
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        if type(secondDict[key]).__name__=='dict':#test to see if the nodes are dictonaires, if not they are leaf nodes
            thisDepth = 1 + getTreeDepth(secondDict[key])
        else:   thisDepth = 1
        if thisDepth > maxDepth: maxDepth = thisDepth
    return maxDepth

def plotNode(nodeTxt, centerPt, parentPt, nodeType):
    createPlot.ax1.annotate(nodeTxt, xy=parentPt,  xycoords='axes fraction',
             xytext=centerPt, textcoords='axes fraction',
             va="center", ha="center", bbox=nodeType, arrowprops=arrow_args )
    
def plotMidText(cntrPt, parentPt, txtString):
    xMid = (parentPt[0]-cntrPt[0])/2.0 + cntrPt[0]
    yMid = (parentPt[1]-cntrPt[1])/2.0 + cntrPt[1]
    createPlot.ax1.text(xMid, yMid, txtString, va="center", ha="center", rotation=30)

def plotTree(myTree, parentPt, nodeTxt):#if the first key tells you what feat was split on
    numLeafs = getNumLeafs(myTree)  #this determines the x width of this tree
    depth = getTreeDepth(myTree)
    firstStr = list(myTree.keys())[0]     #the text label for this node should be this
    cntrPt = (plotTree.xOff + (1.0 + float(numLeafs))/2.0/plotTree.totalW, plotTree.yOff)
    plotMidText(cntrPt, parentPt, nodeTxt)
    plotNode(firstStr, cntrPt, parentPt, decisionNode)
    secondDict = myTree[firstStr]
    plotTree.yOff = plotTree.yOff - 1.0/plotTree.totalD
    for key in secondDict.keys():
        if type(secondDict[key]).__name__=='dict':#test to see if the nodes are dictonaires, if not they are leaf nodes   
            plotTree(secondDict[key],cntrPt,str(key))        #recursion
        else:   #it's a leaf node print the leaf node
            plotTree.xOff = plotTree.xOff + 1.0/plotTree.totalW
            plotNode(secondDict[key], (plotTree.xOff, plotTree.yOff), cntrPt, leafNode)
            plotMidText((plotTree.xOff, plotTree.yOff), cntrPt, str(key))
    plotTree.yOff = plotTree.yOff + 1.0/plotTree.totalD
#if you do get a dictonary you know it's a tree, and the first element will be another dict

def createPlot(inTree):
    fig = plt.figure(1, facecolor='white')
    fig.clf()
    axprops = dict(xticks=[], yticks=[])
    createPlot.ax1 = plt.subplot(111, frameon=False, **axprops)    #no ticks
    #createPlot.ax1 = plt.subplot(111, frameon=False) #ticks for demo puropses 
    plotTree.totalW = float(getNumLeafs(inTree))
    plotTree.totalD = float(getTreeDepth(inTree))
    plotTree.xOff = -0.5/plotTree.totalW; plotTree.yOff = 1.0;
    plotTree(inTree, (0.5,1.0), '')
    plt.show()

#def createPlot():
#    fig = plt.figure(1, facecolor='white')
#    fig.clf()
#    createPlot.ax1 = plt.subplot(111, frameon=False) #ticks for demo puropses 
#    plotNode('a decision node', (0.5, 0.1), (0.1, 0.5), decisionNode)
#    plotNode('a leaf node', (0.8, 0.1), (0.3, 0.8), leafNode)
#    plt.show()

def retrieveTree(i):
    listOfTrees =[{'no surfacing': {0: 'no', 1: {'flippers': {0: 'no', 1: 'yes'}}}},{'R': {1: {'C': {1: {'S': {1: {'A': {1: {'P': {0: 0, 1: 1}}, 2: 0}}, 2: {'A': {1: {'L': {1: {'P': {0: 0, 1: 1}}, 2: 0}}, 2: 1, 3: 0}}, 3: {'A': {0: 0, 2: 2, 3: 3}}}}, 2: {'S': {1: {'L': {1: {'A': {1: {'P': {0: 0, 1: 1}}, 2: 0}}, 2: {'P': {1: {'A': {1: 0, 2: 0}}, 2: 0}}}}, 2: {'L': {1: {'A': {1: {'P': {1: 1, 2: 1}}, 2: {'P': {0: 0, 1: 1, 2: 2}}, 3: 1}}, 2: {'A': {1: {'P': {1: 1, 2: 1}}, 2: {'P': {1: 1, 2: 2}}}}}}, 3: {'L': {1: 1, 2: {'A': {1: 1, 3: 3}}}}}}, 3: {'S': {2: {'A': {1: 1, 2: {'P': {2: 2, 3: 3}}}}, 3: {'A': {1: {'L': {1: {'P': {0: 0, 2: 2}}, 2: 2}}, 2: 4}}}}}}, 2: {'S': {1: {'C': {1: {'P': {1: 0, 2: 1}}, 2: {'L': {1: {'A': {1: 1, 2: 2}}, 2: 2}}}}, 2: {'C': {1: {'P': {2: 2, 3: 3}}, 2: {'P': {1: {'A': {1: {'L': {1: 1, 2: 2}}, 2: {'L': {1: 2, 2: 1}}}}, 2: {'A': {1: {'L': {1: 1, 2: 3}}, 2: {'L': {2: 2, 4: 4}}}}, 3: 4}}, 3: {'P': {1: {'A': {1: 1, 3: 3, 4: 4}}, 3: 2}}}}, 3: {'C': {2: {'A': {1: {'P': {1: 3, 2: 4, 3: 3}}, 2: 2}}, 3: 4}}}}, 3: {'P': {1: {'S': {1: {'C': {1: 0, 2: {'L': {1: {'A': {1: 1, 2: 0}}, 3: 0}}}}, 2: {'L': {1: 0, 2: {'A': {1: {'C': {0: 0, 2: 2}}, 2: 0, 3: 0}}, 3: {'C': {2: {'A': {1: 4, 2: 0}}, 3: 5}}}}, 3: 4}}, 2: {'C': {1: {'S': {1: {'A': {0: 0, 1: 1}}, 2: 0}}, 2: {'A': {1: {'L': {1: {'S': {0: 0, 2: 2}}, 2: {'S': {0: 0, 4: 4}}}}, 2: {'S': {2: {'L': {0: 0, 2: 2, 3: 3}}, 3: 0}}, 3: {'L': {1: 0, 2: 3, 3: 4}}}}, 3: {'A': {1: {'L': {3: 3, 4: 4}}, 2: 0, 3: {'S': {2: 4, 3: {'L': {4: 4, 5: 5}}}}}}}}, 3: {'A': {1: {'S': {1: {'L': {1: 0, 2: {'C': {0: 0, 2: 2}}, 3: 0}}, 2: 0, 3: 0}}, 2: {'L': {1: 0, 2: 0, 3: {'S': {1: 0, 2: {'C': {1: 0, 2: 0}}, 3: 0}}}}, 3: {'L': {1: 0, 2: {'C': {1: 0, 2: {'S': {2: 0, 3: 4}}, 3: 0}}, 3: {'C': {1: {'S': {0: 0, 3: 3}}, 2: {'S': {2: 5, 3: 5}}, 3: 0}}}}}}}}}}]
    return listOfTrees[i]

createPlot(retrieveTree(1))
