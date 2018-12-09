import matplotlib.pyplot as plt
import fileintonumpy as fp
from numpy import *

# Get the dataset and the label from the file 
dataset , label = fp.filereader("datingTestSet2.txt")

fig = plt.figure()
ax1 = fig.add_subplot(221)
ax1.scatter(dataset[ : , 0] , dataset[ : , 1] , 15 * array(label) , 15 * array(label))

ax2 = fig.add_subplot(222)
ax2.scatter(dataset[ : , 0] , dataset[ : , 2] , 15 * array(label) , 15 * array(label))

ax3 = fig.add_subplot(223)
ax3.scatter(dataset[ : , 1] , dataset[ : , 2] , 15 * array(label) , 15 * array(label))


plt.show()
