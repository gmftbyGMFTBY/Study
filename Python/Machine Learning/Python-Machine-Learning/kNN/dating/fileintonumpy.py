import numpy as np

def filereader(filename):
    '''
        This function try to get the filename 
        and read the data set from the file into 
        the numpy ndarray class to return.

        Input :
            filename - string class , name of the file 
        Output : 
            numpy ndarray tuple
            1. dataset - the ndarray which shape is (N , 3)
            2. label - the ndarray which shape is (N , 1)
    '''
    with open("datingTestSet2.txt" , 'r') as f :
        item = []
        for i in f :
            # Change the data into one item and 
            # fix them into the number not the string
            inner = i.split()
            for j in range(len(inner)):
                inner[j] = float(inner[j])
            item.append(inner)
        origin = np.array(item)
        dataset = origin[ : , :3]
        label = origin[ : , 3]
    return dataset , label


