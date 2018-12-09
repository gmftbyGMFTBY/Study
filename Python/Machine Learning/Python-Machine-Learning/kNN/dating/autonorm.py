#!/usr/bin/python3

import fileintonumpy as gp
import numpy as np

def autonorm(dataset):
    '''
        This function is try to fix the array of the number
        Because the number is so unbalanced , so we should
        auto norm the number to balanced the data.

        Input :
            dataset - the numpy ndarray class which need to be autonormed
        Output :
            (new)dataset - the new dataset from the dataset which shape is (N , 3)
            ranges - the shape is (N , 1) present the range of the dataset in each low
            minval - the shape is (N , 1) present the minivalue of the dataset in each low
    '''
    mini = np.min(dataset , axis = 0)   # mini
    ranges = np.ptp(dataset , axis = 0)    # ranges
    dataset = (dataset - mini) / ranges    # auto norm

    return dataset , ranges , mini



