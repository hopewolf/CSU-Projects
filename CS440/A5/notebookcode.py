
# coding: utf-8

# $\newcommand{\xv}{\mathbf{x}}
# \newcommand{\Xv}{\mathbf{X}}
# \newcommand{\yv}{\mathbf{y}}
# \newcommand{\zv}{\mathbf{z}}
# \newcommand{\av}{\mathbf{a}}
# \newcommand{\Wv}{\mathbf{W}}
# \newcommand{\wv}{\mathbf{w}}
# \newcommand{\tv}{\mathbf{t}}
# \newcommand{\Tv}{\mathbf{T}}
# \newcommand{\muv}{\boldsymbol{\mu}}
# \newcommand{\sigmav}{\boldsymbol{\sigma}}
# \newcommand{\phiv}{\boldsymbol{\phi}}
# \newcommand{\Phiv}{\boldsymbol{\Phi}}
# \newcommand{\Sigmav}{\boldsymbol{\Sigma}}
# \newcommand{\Lambdav}{\boldsymbol{\Lambda}}
# \newcommand{\half}{\frac{1}{2}}
# \newcommand{\argmax}[1]{\underset{#1}{\operatorname{argmax}}}
# \newcommand{\argmin}[1]{\underset{#1}{\operatorname{argmin}}}$

# # Assignment 5: Neural Networks

# *Drew Boston*

# ## Overview

# Here is my code that trains neural networks of various numbers of hidden layers and units in each hidden layer and returns results as specified below.  I have included various test cases throughout the notebook, as well as two major applications of these methods; one regression problem and one classification problem. 

# ## Required Code

# For this notebook to work, it requires the following files:
# 
# Download [nn2.tar](http://www.cs.colostate.edu/~anderson/cs440/notebooks/nn2.tar) (provided by Professor Anderson) and extract its contents, which are
# 
# * `neuralnetworks.py`
# * `scaledconjugategradient.py`
# * `mlutils.py`

# I've grouped the various imports necessary here.

# In[32]:

import numpy as np
import matplotlib.pyplot as plt
get_ipython().magic('matplotlib inline')
import neuralnetworks as nn
import mlutils as ml
import time
import sys


# **checkAccuracy(A,B):**
# 
# While I could use properties of neuralnetworks (specifically error trace) to eliminate this function, I already had it written and prefer to use my own implementations when possible! :)
# 
# So, this function will return the percentage of incorrect classifications based on A and B provided to it, where A is the predicted values, and B is the actual (i.e. target) values.

# In[33]:

#note: calculates percentage of incorrect classifications, NOT correct classifications. I believe this is correct - double check results!
def checkAccuracy(A, B):
    count = 0
    num = len(B)
    for i in range(num):
        if A[i] != B[i]:
            count += 1
    return (count/num)
    


# **trainNNs(X, T, trainFraction, hiddenLayerStructures, numberRepetitions, numberIterations, classify=False):**
# 
# This function follows the general outline provided to us in the assignment page. I have commented throughout to further explain what occurs at each major step.

# In[107]:

def trainNNs(X, T, trainFraction, hiddenLayerStructures, numberRepetitions, numberIterations, classify=False):
    
    #results will be a list of [hiddenLayer, trainPerformance, testPerformance, time], one per each hiddenLayer
    results = []
    
    ##need to check for classification problem and adjust accordingly !
    
    for hiddenLayer in hiddenLayerStructures:
        trainPerformance = []  #training errors
        testPerformance = []  #testing errors
        times = []  #training times
        startTime = time.time()
        for i in range(numberRepetitions):
            #Xtrain is training data, results of which are contrasted to Ttrain
            #Xtest is testing data, results of which are contrasted against Ttest
            Xtrain, Ttrain, Xtest, Ttest = ml.partition(X, T, (trainFraction, (1-trainFraction)), classification=classify)
            #now we check for classification vs. non-classification:
            
            if classify:
                nnet = nn.NeuralNetworkClassifier(X.shape[1], hiddenLayer, len(np.unique(T)))
                nnet.train(Xtrain, Ttrain, numberIterations)
                #now net is created / trained, need to check accuracy of predictions now (Ctrain/Ctest)
                Ctrain = nnet.use(Xtrain)
                Ctest = nnet.use(Xtest)
                trainAcc = checkAccuracy(Ctrain, Ttrain)
                testAcc = checkAccuracy(Ctest, Ttest)
            
            #if not classify, then:
            #note; could combine a lot of this if-else statement, but keeping it this way for easier reading.
            #shouldn't affect runtimes hardly at all (nanoseconds)
           
            else:
                nInputs = Xtrain.shape[1]
                nOutputs = Ttrain.shape[1]   #following from notebook 16 In[19]
                nnet = nn.NeuralNetwork(nInputs, hiddenLayer, nOutputs)
                nnet.train(Xtrain, Ttrain, nIterations = numberIterations)
                #now net is created / trained, need to check accuracy of predictions now (Ctrain/Ctest)
                Ctrain = nnet.use(Xtrain)
                Ctest = nnet.use(Xtest)
                #using root mean square error, check accuracy of nnet predictions:
                trainAcc = np.sqrt(np.mean((Ctrain-Ttrain)**2))
                testAcc = np.sqrt(np.mean((Ctest-Ttest)**2))
            
            #append train and test accuracy to appropriate lists
            trainPerformance.append(trainAcc)
            testPerformance.append(testAcc)
        
        #finished all training / accuracy testing for this hiddenLayer, so stop time
        endTime = time.time()
        #add to results:
        results.append([hiddenLayer, trainPerformance, testPerformance, endTime-startTime])
    return results
            
            


# **summarize(results):**
# 
# This function replaces individual errors (i.e. training performances; there will be one per repetition) by the mean of all errors.

# In[108]:

def summarize(results):
    summary = []
    
    #note: result (below) will have form:
    #[hiddenLayer, trainPerformance, testPerformance, time]
    for result in results:
        meanTrain = np.mean(np.array(result[1]))
        meanTest = np.mean(np.array(result[2]))
        #keep hiddenLayer and time the same, but change middle entries to mean values
        summary.append([result[0], meanTrain, meanTest, result[3]])
    return summary  


# **bestNetwork(summary):**
# 
# This function takes the output from `summarize(results)` (not directly; must be called with the output) and returns the network with the minimum error for a particular hidden layer structure.

# In[109]:

def bestNetwork(summary):
    #note: concerned only with minimum testing error, not training !!
    minTest = float("inf")
    bestNet = []
    #iterate through summary "nets" checking for one with smallest meanTest value
    for net in summary:
        if net[2] < minTest:
            minTest = net[2]
            bestNet = net
    return bestNet
    


# **plotErrorTrace(net):**
# 
# This function simply plots the error trace for a given net.

# In[212]:

def plotErrorTrace(net):
    errors = nnet.getErrorTrace()
    plt.figure()
    plt.plot(range(len(errors)), nnet.getErrorTrace());


# ## Basic Test Cases
# 

# In[112]:

X = np.arange(10).reshape((-1,1))
T = X + 1 + np.random.uniform(-1, 1, ((10,1)))


# In[113]:

plt.plot(X, T, 'o-');


# In[114]:

nnet = nn.NeuralNetwork(X.shape[1], 2, T.shape[1])
nnet.train(X, T, 100)
nnet.getErrorTrace()


# In[115]:

nnet = nn.NeuralNetwork(X.shape[1], [5, 5, 5], T.shape[1])
nnet.train(X, T, 100)
nnet.getErrorTrace()


# In[116]:

results = trainNNs(X, T, 0.8, [2, 10, [10, 10]], 5, 100, classify=False)
results


# In[117]:

results = trainNNs(X, T, 0.8, [0, 1, 2, 10, [10, 10], [5, 5, 5, 5], [2]*5], 50, 100, classify=False)


# In[118]:

summarize(results)


# In[119]:

best = bestNetwork(summarize(results))
print(best)
print('Hidden Layers {} Average RMSE Training {:.2f} Testing {:.2f} Took {:.2f} seconds'.format(*best))


# We are seeing the expected results here, so I will move on to the regression experiment!

# ## Data for Regression Experiment
# 
# From the UCI Machine Learning Repository, download the [Appliances energy prediction](http://archive.ics.uci.edu/ml/datasets/Appliances+energy+prediction) data.  You can do this by visiting the Data Folder for this data set, or just do this:
# 
#      !wget http://archive.ics.uci.edu/ml/machine-learning-databases/00374/energydata_complete.csv
# 
# 

# I used wget (commented out below to prevent multiple downloads when re-running notebook) to download the file. 

# In[125]:

#!wget http://archive.ics.uci.edu/ml/machine-learning-databases/00374/energydata_complete.csv


# Because of the piazza post [here](https://piazza.com/class/jl2i7paafyf49w?cid=236) (where Professor Anderson commented), I believe it is best/acceptable to use Pandas to read the csv file. I found it a lot easier, anyway! Especially as I have experience with dataFrames from CS435 (Big Data).
# 
# Per the assignment instructions, I ignored the first column of each row which contains a data and time, as well as the last two columns of random variables. They will not be used in our modeling of this data. 

# In[152]:

import pandas


# In[169]:

data = pandas.read_csv('energydata_complete.csv')


# As you can see, pandas (or, really, the dataframe structure) formats the data quite nicely into a much more readable format.

# In[170]:

data


# Here we delete the columns mentioned above, as they are not pertinent to our data.

# In[172]:

del data['date']
del data['rv1']
del data['rv2']


# In[173]:

data.shape


# In[191]:

data.iloc[:2,:]


# Use the first two columns, labelled `Appliances` and `lights` as the target variables, and the remaining 24 columns as the input features.  So

# In[192]:

XenergyDF = data.iloc[:,2:]
TenergyDF = data.iloc[:,:2]


# In[193]:

XenergyDF.shape, TenergyDF.shape


# Xnames and Tnames are not used in the network training process, but I created them anyway to verify I had the correct dataframe as opposed to the examples provided in the assignment page.

# In[194]:

Xnames = list(XenergyDF)
Xnames


# In[195]:

Tnames = list(TenergyDF)
Tnames


# Obviously, I need to convert from a dataframe to an np array before I can train on the data, as my trainNNs function was not set up to allow dataframes.

# In[198]:

Xenergy = XenergyDF.values
Tenergy = TenergyDF.values


# In[202]:

Xenergy.shape, Tenergy.shape


# Train several neural networks on all of this data for 100 iterations.  Plot the error trace (nnet.getErrorTrace()) to help you decide now many iterations might be needed.  100 may not be enough.  If for your larger networks the error is still decreasing after 100 iterations you should train all nets for more than 100 iterations.
# 
# Now use your `trainNNs`, `summarize`, and `bestNetwork` functions on this data to investigate various network sizes.

# In[203]:

results = trainNNs(Xenergy, Tenergy, 0.8, [0, 5, [5, 5], [10, 10]], 10, 100)


# In[204]:

summarize(results)


# In[206]:

bestNetwork(summarize(results))


# Here you can see the error trace drops significantly in the first 30-40 repetitions; I believe 100 will work fine here (but I'll know for sure after the next test with 10 different hidden layers).

# In[213]:

plotErrorTrace(nnet)


# Test at least 10 different hidden layer structures.  Larger numbers of layers and units may do the best on training data, but not on testing data. Why?
# 
# Now train another network with your best hidden layer structure on 0.8 of the data and use the trained network on the testing data (the remaining 0.2 of the date).  As before use `ml.partition` to produce the training and testing sets.
# 
# For the testing data, plot the predicted and actual `Appliances` energy use, and the predicted and actual `lights` energy use, in two separate plots.  Discuss what you see.

# Here is my test with 10 different hidden layer structures. I tried to very the dimensions to get a better idea of an ideal structure.

# In[219]:

hiddenLayersList = []

hiddenLayersList.append(4)
hiddenLayersList.append([3,3])
hiddenLayersList.append([5,5])
hiddenLayersList.append([7,5])
hiddenLayersList.append([7,7])
hiddenLayersList.append([7,10])
hiddenLayersList.append([10,7])
hiddenLayersList.append([10,10])
hiddenLayersList.append([14,14])
hiddenLayersList.append([18,18])


# In[220]:

results = trainNNs(Xenergy, Tenergy, 0.8, hiddenLayersList, 10, 100)


# Here are the results of the different hidden layer structures:

# In[221]:

summarize(results)


# In[222]:

bestNetwork(summarize(results))


# Because my largest hidden layer experiment did best, I'm going to repeat it with several more different hidden layers more closely centered around [18,18] to ensure I have the best possible hidden layer structure.

# In[223]:

hiddenLayersList = []

hiddenLayersList.append([18,18])
hiddenLayersList.append([20,20])
hiddenLayersList.append([25,25])
hiddenLayersList.append([30,30])
hiddenLayersList.append([35,35])


# In[224]:

results = trainNNs(Xenergy, Tenergy, 0.8, hiddenLayersList, 10, 100)


# In[225]:

summarize(results)


# In[226]:

bestNetwork(summarize(results))


# First, checking to make sure the error trace for the last hiddenLayer trained [35,35] is still going towards 0 quickly enough (within 100 repetitions):

# In[227]:

plotErrorTrace(nnet)


# Looks good! Also, from above, we can see that the ideal network is again at the end of the range I provided it (although it is higher than the [18,18] hidden layer net from the first round of tests - not this time, however).
# So, I'll ramp up the testing one more time:

# In[228]:

hiddenLayersList = []
hiddenLayersList.append([18,18])
hiddenLayersList.append([35,35])
hiddenLayersList.append([50,50])
hiddenLayersList.append([75,75])


# In[229]:

results = trainNNs(Xenergy, Tenergy, 0.8, hiddenLayersList, 10, 100)


# In[230]:

summarize(results)


# In[231]:

bestNetwork(summarize(results))


# Checking the error trace is still ok with 100 iterations for the last net trained (with hidden layer = [75,75]):

# In[232]:

plotErrorTrace(nnet)


# Yepp! Still good, so we can assume it is fine for the smaller hidden layer nets as well. So, now we just need to plot the accuracy of the best net's predictions for appliances and lights.

# So, we have had three best hidden layer structures throughout our testing, all with testing errors relatively close to one another:
# 
# * `[18, 18], 61.862113397082304, 62.44509378975321, 72.16344404220581]`
# * `[35, 35], 61.57210097923813, 62.60669095059052, 130.78503918647766]`
# * `[50, 50], 62.00144268221696, 62.87340836606546, 185.77634191513062]`
# 
# However, we had the overall minimum error using hidden layer structure [35,35], so that is what I will use going on to the next part.

# In[261]:

startTime = time.time()
Xtrain, Ttrain, Xtest, Ttest = ml.partition(Xenergy, Tenergy, (0.8, 0.2), classification=False)
nnet = nn.NeuralNetwork(Xenergy.shape[1], [35,35], Tenergy.shape[1])
nnet.train(Xtrain, Ttrain, 100)
Ctrain = nnet.use(Xtrain)
Ctest = nnet.use(Xtest)
trainAcc = np.sqrt(np.mean((Ctrain-Ttrain)**2))
testAcc = np.sqrt(np.mean((Ctest-Ttest)**2))
endTime = time.time()


# Now for the plots:

# Appliances (predicted vs. actual):

# In[277]:

plt.subplot(1,1,1)
#using [:,:1] for appliance data
plt.plot(Ttest[:,:1], 'o', Ctest[:,:1],'x')
plt.text(8,12, 'Layer {}'.format(5))
plt.legend(('Test Target','Test NN Output'),loc='upper right',
            prop={'size':9});


# In[279]:

plt.subplot(1,1,1)
#using [:,1:] for lights data
plt.plot(Ttest[:,1:], 'o', Ctest[:,1:],'x')
plt.text(8,12, 'Layer {}'.format(5))
plt.legend(('Test Target','Test NN Output'),loc='upper right',
            prop={'size':9});


# As you can see, there is a pretty wide spread of predictions for this data. I believe this is due to a wide, sporadic variety in appliance energy usage (as seen by the orange 'x's in the graphs above), making it difficult to approximate using a neural network. However, it does seem to have done relatively well; I imagine it could do even better with further fine-tuning.

# ## Data for Classification Experiment
# 
# From the UCI Machine Learning Repository, download the [Anuran Calls (MFCCs)](http://archive.ics.uci.edu/ml/datasets/Anuran+Calls+%28MFCCs%29) data.  You can do this by visiting the Data Folder for this data set, or just do this:
# 
#      !wget 'http://archive.ics.uci.edu/ml/machine-learning-databases/00406/Anuran Calls (MFCCs).zip'
#      !unzip Anuran*zip
#      
# Read the data in the file `Frogs_MFCCs.csv` into python.  This will be a little tricky. Each line of the file is a sample of audio features plus three columns that label the sample by family, genus, and species. We will try to predict the species.  The tricky part is that the species is given as text.  We need to convert this to a target class, as an integer. The `numpy` function `unique` will come in handy here.

# In[21]:

Xanuran.shape, Tanuran.shape


# In[22]:

Xanuran[:2,:]


# In[23]:

Tanuran[:2]


# In[24]:

for i in range(10):
    print('{} samples in class {}'.format(np.sum(Tanuran==i), i))


# In[25]:

results = trainNNs(Xanuran, Tanuran, 0.8, [0, 5, [5, 5]], 5, 100, classify=True)


# In[26]:

summarize(results)


# In[27]:

bestNetwork(summarize(results))


# Now do an investigation like you did for the regression data. 
# 
# Test at least 10 different hidden layer structures. Then train another network with your best hidden layer structure on 0.8 of the data and use the trained network on the testing data (the remaining 0.2 of the date). 
# 
# Plot the predicted and actual `Species` for the testing data as an integer.  Discuss what you see.

# ## Grading
# 
# Download [A5grader.tar](http://www.cs.colostate.edu/~anderson/cs440/notebooks/A5grader.tar) and extract `A5grader.py` from it.

# In[72]:

get_ipython().magic('run -i "A5grader.py"')


# ## Check-in

# Do not include this section in your notebook.
# 
# Name your notebook ```Lastname-A5.ipynb```.  So, for me it would be ```Anderson-A5.ipynb```.  Submit the file using the ```Assignment 5``` link on [Canvas](https://colostate.instructure.com/courses/68135).

# ## Extra Credit
# 
#   2. Repeat the above regression and classification experiments with a second regression data set and a second classification data set.
#   
#   2. Since you are collecting the performance of all repetitions for each network structure, you can calculate a confidence interval about the mean, to help judge significant differences. Do this for either the regression or the classification data and plot the mean test performance with confidence intervals for each network structure tested.  Discuss the statistical significance of the differences among the means.  One website I found to help with this is the site [Correct way to obtain confidence interval with scipy](https://stackoverflow.com/questions/28242593/correct-way-to-obtain-confidence-interval-with-scipy).
#   
# 

# coding: utf-8

# $\newcommand{\xv}{\mathbf{x}}
# \newcommand{\Xv}{\mathbf{X}}
# \newcommand{\yv}{\mathbf{y}}
# \newcommand{\zv}{\mathbf{z}}
# \newcommand{\av}{\mathbf{a}}
# \newcommand{\Wv}{\mathbf{W}}
# \newcommand{\wv}{\mathbf{w}}
# \newcommand{\tv}{\mathbf{t}}
# \newcommand{\Tv}{\mathbf{T}}
# \newcommand{\muv}{\boldsymbol{\mu}}
# \newcommand{\sigmav}{\boldsymbol{\sigma}}
# \newcommand{\phiv}{\boldsymbol{\phi}}
# \newcommand{\Phiv}{\boldsymbol{\Phi}}
# \newcommand{\Sigmav}{\boldsymbol{\Sigma}}
# \newcommand{\Lambdav}{\boldsymbol{\Lambda}}
# \newcommand{\half}{\frac{1}{2}}
# \newcommand{\argmax}[1]{\underset{#1}{\operatorname{argmax}}}
# \newcommand{\argmin}[1]{\underset{#1}{\operatorname{argmin}}}$

# # Assignment 5: Neural Networks

# Luke Burford

# ## Overview

# You will write and apply code that trains neural networks of various numbers of hidden layers and units in each hidden layer and returns results as specified below.  You will do this once for a regression problem and once for a classification problem. 

# ## Required Code

# Download [nn2.tar](http://www.cs.colostate.edu/~anderson/cs440/notebooks/nn2.tar) that was used in lecture and extract its contents, which are
# 
# * `neuralnetworks.py`
# * `scaledconjugategradient.py`
# * `mlutils.py`

# Write the following functions that train and evaluate neural network models.
# 
# * `results = trainNNs(X, T, trainFraction, hiddenLayerStructures, numberRepetitions, numberIterations, classify)`
# 
# The arguments to `trainNNs` are
# 
# * `X` is a matrix of input data of shape `nSamples x nFeatures`
# * `T` is a matrix of target data of shape `nSamples x nOutputs`
# * `trainFraction` is fraction of samples to use as training data. 1-`trainFraction` is number of samples for testing data
# * `hiddenLayerStructures` is list of network architectures. For example, to test two networks, one with one hidden layer of 20 units, and one with 3 hidden layers with 5, 10, and 20 units in each layer, this argument would be `[[20], [5, 10, 20]]`.
# * `numberRepetitions` is number of times to train a neural network.  Calculate training and testing average performance (two separate averages) of this many training runs.
# * `numberIterations` is the number of iterations to run the scaled conjugate gradient algorithm when a neural network is trained.
# * `classify` is set to `True` if you are doing a classification problem, in which case `T` must be a single column of target class integers.
# 
# This function returns `results` which is list with one element for each network structure tested.  Each element is a list containing 
# 
# * the hidden layer structure (as a list),
# * a list of training data performance for each repetition, 
# * a list of testing data performance for each repetition, and
# * the number of seconds it took to run this many repetitions for this network structure.
# 
# This function should follow these steps:
# 
#   * For each network structure given in `hiddenLayerStructures`
#     * For numberRepetitions
#       * Use `ml.partition` to randomly partition X and T into training and testing sets.
#       * Create a neural network of the given structure
#       * Train it for numberIterations
#       * Use the trained network to produce outputs for the training and for the testing sets
#       * If classifying, calculate the fraction of samples incorrectly classified for training and testing sets.
#        Otherwise, calculate the RMSE of training and testing sets.
#       * Add the training and testing performance to a collection (such as a list) for this network structure
#     * Add to a collection of all results the hidden layer structure, lists of training performance and testing performance, and seconds taken to do these repetitions.
#   * return the collection of all results

# Also write the following two functions. `summarize(results)` returns a list of lists like `results` but with the list of training performances replaced by their mean and the list of testing performances replaced by their mean.   
# `bestNetwork(summary)` takes the output of `summarize(results)` and returns the best element of `results`, determined by the element that has the smallest test performance.
# 
# * `summary = summarize(results)` where `results` is returned by `trainNNs` and `summary` is like `results` with the training and testing performance lists replaced by their means
# * `best = bestNetwork(summary)` where `summary` is returned by `summarize` and `best` is the best element of `summary`

# In[490]:

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
get_ipython().magic('matplotlib inline')
import neuralnetworks as nn
import mlutils as ml
import time
import sys


# 

# In[576]:

#note: calculates percentage of incorrect classifications, NOT correct classifications. I believe this is correct - double check results!
def checkAcc(A, B):
    checkC = 0
    numLen = len(B)
    for i in range(numLen):
        if A[i] != B[i]:
            checkC += 1
    return (checkC/numLen) 


# **trainNNs(X, T, trainFraction, hiddenLayerStructures, numberRepetitions, numberIterations, classify=False):**
# 
# This is the backbone to the entire project, it follows more or less, what is described in the assignment page.

# In[492]:

def trainNNs(X, T, trainFraction, hiddenLayerStructures, numberRepetitions, numberIterations, classify=False):
    
    results = [] #results will be in the format: [hiddenLayer, trainPerf, testPerf, time], and each hiddenLayer will contain this
    
    for hiddenLayer in hiddenLayerStructures:
        trainPerf = []  #training errors
        testPerf = []  #testing errors
        times = []  #training times
        start = time.time()
        for i in range(numberRepetitions):
            
            #Xtrain is training data, results of which are contrasted to Ttrain
            #Xtest is testing data, results of which are contrasted against Ttest
            Xtrain, Ttrain, Xtest, Ttest = ml.partition(X, T, (trainFraction, (1-trainFraction)), classification=classify)

            #next check for classification vs. non-classification:
            if classify:
                nnet = nn.NeuralNetworkClassifier(X.shape[1], hiddenLayer, len(np.unique(T)))
                nnet.train(Xtrain, Ttrain, numberIterations)
                #now net is created / trained, need to check accuracy of predictions now (Ctrain/Ctest)
                Ctrain = nnet.use(Xtrain)
                Ctest = nnet.use(Xtest)
                trainAcc = checkAcc(Ctrain, Ttrain)
                testAcc = checkAcc(Ctest, Ttest)
            
            
            #else:
            #shouldn't affect runtimes hardly at all (nanoseconds)
            else:
                nIn = Xtrain.shape[1]
                nOut = Ttrain.shape[1]
                nnet = nn.NeuralNetwork(nIn, hiddenLayer, nOut)
                nnet.train(Xtrain, Ttrain, nIterations = numberIterations)
                #now need to check accuracy of predictions
                Ctrain = nnet.use(Xtrain)
                Ctest = nnet.use(Xtest)
                #using root mean square error, check accuracy of nnet predictions:
                trainAcc = np.sqrt(np.mean((Ctrain-Ttrain)**2))
                testAcc = np.sqrt(np.mean((Ctest-Ttest)**2))
        
            trainPerf.append(trainAcc)
            testPerf.append(testAcc)
        
        endTime = time.time()
        results.append([hiddenLayer, trainPerf, testPerf, endTime-start])
    return results


# **summarize(results):**
# 
# Summarize will replace individual errors by the mean of all errors.

# In[493]:

def summarize(results):
    summary = []
    #[hiddenLayer, trainPerformance, testPerformance, time]
    for result in results:
        meanTrain = np.mean(np.array(result[1]))
        meanTest = np.mean(np.array(result[2]))
        summary.append([result[0], meanTrain, meanTest, result[3]])
    return summary  


# **bestNetwork(summary):**
# 
# bestNetwork will take the output from `summarize(results)` and returns the best network (i.e. the network with the minimum error for a specific hidden layer)

# In[494]:

def bestNetwork(summary):
    minT = float("inf")
    bestN = []
    for net in summary:
        if net[2] < minT:
            minT = net[2]
            bestN = net
    return bestN


# ## Examples
# 

# In[495]:

X = np.arange(10).reshape((-1,1))
T = X + 1 + np.random.uniform(-1, 1, ((10,1)))


# In[496]:

import matplotlib.pyplot as plt
get_ipython().magic('matplotlib inline')


# In[497]:

plt.plot(X, T, 'o-');


# In[498]:

nnet = nn.NeuralNetwork(X.shape[1], 2, T.shape[1])
nnet.train(X, T, 100)
nnet.getErrorTrace()


# In[499]:

nnet = nn.NeuralNetwork(X.shape[1], [5, 5, 5], T.shape[1])
nnet.train(X, T, 100)
nnet.getErrorTrace()


# In[500]:

results = trainNNs(X, T, 0.8, [2, 10, [10, 10]], 5, 100, classify=False)
results


# In[501]:

results = trainNNs(X, T, 0.8, [0, 1, 2, 10, [10, 10], [5, 5, 5, 5], [2]*5], 50, 100, classify=False)


# In[502]:

summarize(results)


# In[503]:

best = bestNetwork(summarize(results))
print(best)
print('Hidden Layers {} Average RMSE Training {:.2f} Testing {:.2f} Took {:.2f} seconds'.format(*best))


# Hummm...neural nets with no hidden layers did best on this simple data set.  Why?  Remember what "best" means.

# ## Data for Regression Experiment
# 
# From the UCI Machine Learning Repository, download the [Appliances energy prediction](http://archive.ics.uci.edu/ml/datasets/Appliances+energy+prediction) data.  You can do this by visiting the Data Folder for this data set, or just do this:
# 
#      !wget http://archive.ics.uci.edu/ml/machine-learning-databases/00374/energydata_complete.csv
# 
# 

# Read this data into python.  One suggestion is to use the `loadtxt` function in the `numpy` package.  You may ignore the first column of each row which contains a data and time.  Also ignore the last two columns of random variables.  We will not use that in our modeling of this data.  You will also have to deal with the double quotes that surround every value in every field.  Read the first line of this file to get the names of the features.
# 
# Once you have read this in correctly, you should see values like this:

# In[504]:

#!wget http://archive.ics.uci.edu/ml/machine-learning-databases/00374/energydata_complete.csv


# I decided to use pandas since it plots in a very nice way and seems easier to parse the file.

# In[505]:

#parse the file using pandas and assign the appropiate values
data= pd.read_csv('energydata_complete.csv')
del data['date']
del data['rv1']
del data['rv2']
XenergyDF = data.iloc[:,2:]
TenergyDF = data.iloc[:,:2]
Xnames = list(XenergyDF)
Tnames = list(TenergyDF)


# In[506]:

names


# In[507]:

data.shape


# In[508]:

data.head()


# Use the first two columns, labelled `Appliances` and `lights` as the target variables, and the remaining 24 columns as the input features.  So

# In[509]:

Xenergy = XenergyDF.values
Tenergy = TenergyDF.values


# In[510]:

Xenergy.shape, Tenergy.shape


# In[511]:

Xnames


# In[512]:

Tnames


# Train several neural networks on all of this data for 100 iterations.  Plot the error trace (nnet.getErrorTrace()) to help you decide now many iterations might be needed.  100 may not be enough.  If for your larger networks the error is still decreasing after 100 iterations you should train all nets for more than 100 iterations.
# 
# Now use your `trainNNs`, `summarize`, and `bestNetwork` functions on this data to investigate various network sizes.

# In[513]:

results = trainNNs(Xenergy, Tenergy, 0.8, [0, 5, [5, 5], [10, 10]], 10, 100)


# In[514]:

summarize(results)


# In[515]:

bestNetwork(summarize(results))


# **plotET(net):**
# 
# Plots the error trace of a net.

# In[516]:

def plotET(net):
    err = nnet.getErrorTrace()
    plt.figure()
    plt.plot(range(len(err)), nnet.getErrorTrace());


# When looking at a plot for the error trace. It drops drastically by the first 20 or so repetitions.

# In[518]:

plotET(nnet)


# Test at least 10 different hidden layer structures.  Larger numbers of layers and units may do the best on training data, but not on testing data. Why?
# 
# Now train another network with your best hidden layer structure on 0.8 of the data and use the trained network on the testing data (the remaining 0.2 of the date).  As before use `ml.partition` to produce the training and testing sets.
# 
# For the testing data, plot the predicted and actual `Appliances` energy use, and the predicted and actual `lights` energy use, in two separate plots.  Discuss what you see.

# In[519]:

hiddenLayers = []

hiddenLayers.append(2)
hiddenLayers.append([4,4])
hiddenLayers.append([6,6])
hiddenLayers.append([8,8])
hiddenLayers.append([10,10])
hiddenLayers.append([7,14])
hiddenLayers.append([14,7])
hiddenLayers.append([13,13])
hiddenLayers.append([15,15])
hiddenLayers.append([18,18])


# In[520]:

results = trainNNs(Xenergy, Tenergy, 0.8, hiddenLayers, 10, 100)


# In[521]:

summarize(results)


# In[522]:

bestNetwork(summarize(results))


# In[528]:

plotET(nnet)


# It seems that a bigger hiddenLayer yields the best result, so lets test some bigger 
# Now for some more intense tests:

# In[523]:

hiddenLayersList = []
hiddenLayersList.append([20,20])
hiddenLayersList.append([29,29])
hiddenLayersList.append([38,38])
hiddenLayersList.append([60,60])


# In[524]:

results = trainNNs(Xenergy, Tenergy, 0.8, hiddenLayersList, 10, 100)


# In[525]:

summarize(results)


# In[526]:

bestNetwork(summarize(results))


# In[529]:

plotET(nnet)


# It seems that bigger is better until a certain extent. This is most likely capped by overfitting. This seems to require a little trial and error for each different problem.

# In[530]:

start = time.time()
Xtrain, Ttrain, Xtest, Ttest = ml.partition(Xenergy, Tenergy, (0.8, 0.2))
nnet = nn.NeuralNetwork(Xenergy.shape[1], [35,35], Tenergy.shape[1])
nnet.train(Xtrain, Ttrain, 100)
Ctrain = nnet.use(Xtrain)
Ctest = nnet.use(Xtest)
trainAcc = np.sqrt(np.mean((Ctrain-Ttrain)**2))
testAcc = np.sqrt(np.mean((Ctest-Ttest)**2))
endTime = time.time()


# In[543]:

plt.subplot(1,1,1)
plt.plot(Ttest[:,:1], 'o', Ctest[:,:1],'o')
pltz.legend(('Test Target','Test NN Output'),loc='upper right',
            prop={'size':5});


# In[541]:

plt.subplot(1,1,1)
plt.plot(Ttest[:,1:], 'o', Ctest[:,1:],'o')
plt.legend(('Test Target','Test NN Output'),loc='upper right',
            prop={'size':5});


# We seem to have a pretty good coverage of test targert. It has some strange outliers sometimes but I think that this is caused by the wide range of data that the network has to cover

# ## Data for Classification Experiment
# 
# From the UCI Machine Learning Repository, download the [Anuran Calls (MFCCs)](http://archive.ics.uci.edu/ml/datasets/Anuran+Calls+%28MFCCs%29) data.  You can do this by visiting the Data Folder for this data set, or just do this:
# 
#      !wget 'http://archive.ics.uci.edu/ml/machine-learning-databases/00406/Anuran Calls (MFCCs).zip'
#      !unzip Anuran*zip
#      
# Read the data in the file `Frogs_MFCCs.csv` into python.  This will be a little tricky. Each line of the file is a sample of audio features plus three columns that label the sample by family, genus, and species. We will try to predict the species.  The tricky part is that the species is given as text.  We need to convert this to a target class, as an integer. The `numpy` function `unique` will come in handy here.

# I use the command !wget and !unzip as shown below:

# In[550]:

#!wget 'http://archive.ics.uci.edu/ml/machine-learning-databases/00406/Anuran Calls (MFCCs).zip'
#!unzip Anuran*zip


# In[605]:

data = pd.read_csv('Frogs_MFCCs.csv')
Xanuran = data.iloc[:,:22]
TanuranTemp = data['Species']


# In[606]:

TanuranTemp.head()


# In[607]:

classNames = np.unique(TanuranTemp)
classNameDict = {}
for i in range(len(classNames)):
    classNameDict[classNames[i]] = i
    
Tanuran = TanuranTemp.copy()
for i in range(len(TanuranTemp)):
    Tanuran.loc[i] = classNameDict[TanuranTemp.loc[i]]
Tanuran=Tanuran.values.reshape(7195,1)


# In[608]:

Xanuran.shape, Tanuran.shape


# In[609]:

Xanuran.head()


# In[610]:

for i in range(10):
    print('{} samples in class {}'.format(np.sum(Tanuran==i), i))


# In[611]:

Xanuran = XanuranDF.values


# Okay! so it looks like ive got it all parsed in (all be it not very pretty but it does seem to work! Now we can test it with the NN.

# In[612]:

results = trainNNs(Xanuran, Tanuran, 0.8, [0, 5, [5, 5]], 5, 100, classify=True)


# In[613]:

summarize(results)


# In[614]:

bestNetwork(summarize(results))


# In[615]:

plotET(nnet)


# Now do an investigation like you did for the regression data. 
# 
# Test at least 10 different hidden layer structures. Then train another network with your best hidden layer structure on 0.8 of the data and use the trained network on the testing data (the remaining 0.2 of the date). 
# 
# Plot the predicted and actual `Species` for the testing data as an integer.  Discuss what you see.

# In[596]:

hiddenLayers = []

hiddenLayers.append(2)
hiddenLayers.append([4,4])
hiddenLayers.append([6,6])
hiddenLayers.append([8,8])
hiddenLayers.append([10,10])
hiddenLayers.append([7,14])
hiddenLayers.append([14,7])
hiddenLayers.append([13,13])
hiddenLayers.append([15,15])
hiddenLayers.append([60,60])


# In[597]:

results = trainNNs(Xanuran, Tanuran, 0.8, hiddenLayers, 10, 100, classify=True)


# In[598]:

summarize(results)


# In[599]:

bestNetwork(summarize(results))


# In[600]:

plotET(nnet)


# In[591]:

hiddenLayersList = []
hiddenLayersList.append([20,20])
hiddenLayersList.append([29,29])
hiddenLayersList.append([38,38])
hiddenLayersList.append([60,60])


# In[592]:

results = trainNNs(Xanuran, Tanuran, 0.8, hiddenLayers, 10, 100, classify=True)


# In[593]:

summarize(results)


# In[594]:

bestNetwork(summarize(results))


# In[595]:

plotET(nnet)


# Ive tried to work through a bunch of different types of hiddenLayers but I found it very difficult to yield a confident network.
