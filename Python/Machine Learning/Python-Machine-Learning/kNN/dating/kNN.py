import numpy as np


def knn(inx , dataset , label , k):
    '''
        This function is the most important py file in this kNN package
        The fucntion get the dataset and the testdata and try to use the kNN
        Algorithm to make sure the label of the testdata

        I use the Oujilide to calulate the distance between two spots

        Input : 
            1. inx : the test data
            2. dataset : the dataset into the Algorithm
            3. label : the label of every datest
            4. k : the param of the kNN Algorithm
        Output :
            the label of the inx data.
    '''
    label = label.astype(np.int64)

    num = dataset.shape[0]   # the size of the dataset
    parray = dataset - inx    # the diff between dataset and the inx
    parray = parray ** 2    # the power
    parray = np.sum(parray , axis = 1)    # the sum
    parray = parray ** 0.5    # the OJILIDE Distance

    index = np.argpartition(parray , k)[ : k]    # Get the K partition quickly

    ans = label[ index ]    # Get the answer
    ans.shape = ans.shape[0]    # Fix the shape to bincount

    getting = np.bincount(ans)    # Get the answer deeply

    inde = 0    # save the index of the maximum
    p = - np.inf    # Define the float - inf 
    for i , j in enumerate(getting):
        if j > p : 
            inde = i
            p = j

    return inde


