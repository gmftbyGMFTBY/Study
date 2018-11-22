from numpy import *
import fileintonumpy as fp
import autonorm as am
import kNN
# import plot_analyse as pa

def main():
    # Define the part of the data test to use
    part = 0.1
    # Use the filereader to get the date from the file
    datatest , label = fp.filereader("datingTestSet2.txt")
    # Auto norm the datatest
    datatest , ranges , minval = am.autonorm(datatest)

    m = datatest.shape[0]    # the size of the dataset
    errorcount = 0    # Count the error number

    k = int(m * part)    # the size of the test dataset

    for i in range(k):
        p = kNN.knn(datatest[i] , datatest[ k : m ] , label[k : m] , 3)
        if(p != label[i]):
            errorcount += 1
        print("The label is %s , the real label is %s" % (int(label[i]) , p))
    print("The error count of the percentile is %s" % (errorcount * 1.0 / k))

if __name__ == "__main__":
    main()
    print("Prepare to create one Png photograph to show the dataset.")
    import plot_analyse as pa    # import the matplotlib to show the dataset
        




