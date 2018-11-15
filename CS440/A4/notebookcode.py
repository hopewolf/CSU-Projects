
# coding: utf-8

# # Reinforcement Learning Solution to the Towers of Hanoi Puzzle

# For this assignment, you will use reinforcement learning to solve the [Towers of Hanoi](https://en.wikipedia.org/wiki/Tower_of_Hanoi) puzzle.  
# 
# To accomplish this, you must modify the code discussed in lecture for learning to play Tic-Tac-Toe.  Modify the code  so that it learns to solve the three-disk, three-peg
# Towers of Hanoi Puzzle.  In some ways, this will be simpler than the
# Tic-Tac-Toe code.  
# 
# Steps required to do this include the following:
# 
#   - Represent the state, and use it as a tuple as a key to the Q dictionary.
#   - Make sure only valid moves are tried from each state.
#   - Assign reinforcement of $1$ to each move, even for the move that results in the goal state.
# 
# Make a plot of the number of steps required to reach the goal for each
# trial.  Each trial starts from the same initial state.  Decay epsilon
# as in the Tic-Tac-Toe code.

# ## Requirements

# First, how should we represent the state of this puzzle?  We need to keep track of which disks are on which pegs. Name the disks 1, 2, and 3, with 1 being the smallest disk and 3 being the largest. The set of disks on a peg can be represented as a list of integers.  Then the state can be a list of three lists.
# 
# For example, the starting state with all disks being on the left peg would be `[[1, 2, 3], [], []]`.  After moving disk 1 to peg 2, we have `[[2, 3], [1], []]`.
# 
# To represent that move we just made, we can use a list of two peg numbers, like `[1, 2]`, representing a move of the top disk on peg 1 to peg 2.

# Now on to some functions. Define at least the following functions. Examples showing required output appear below.
# 
#    - `printState(state)`: prints the state in the form shown below
#    - `validMoves(state)`: returns list of moves that are valid from `state`
#    - `makeMove(state, move)`: returns new (copy of) state after move has been applied.
#    - `trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF)`: train the Q function for number of repetitions, decaying epsilon at start of each repetition. Returns Q and list or array of number of steps to reach goal for each repetition.
#    - `testQ(Q, maxSteps, validMovesF, makeMoveF)`: without updating Q, use Q to find greedy action each step until goal is found. Return path of states.
# 
# A function that you might choose to implement is
# 
#    - `stateMoveTuple(state, move)`: returns tuple of state and move.  
#     
# This is useful for converting state and move to a key to be used for the Q dictionary.
# 
# Show the code and results for testing each function.  Then experiment with various values of `nRepetitions`, `learningRate`, and `epsilonDecayFactor` to find values that work reasonably well, meaning that eventually the minimum solution path of seven steps is found consistently.
# 
# Make a plot of the number of steps in the solution path versus number of repetitions. The plot should clearly show the number of steps in the solution path eventually reaching the minimum of seven steps, though the decrease will not be monotonic.  Also plot a horizontal, dashed line at 7 to show the optimal path length.
# 
# Add markdown cells in which you describe the Q learning algorithm and your implementation of Q learning as applied to the Towers of Hanoi problem.  Use at least 15 sentences, in one or more markdown cells.

# ## __Helper Functions:__

# The following functions are used to complete the tower of Hanoi puzzle. These functions  were copied from the A4 assignment. The functions declarations are:
# 
#    - `printState(state)`: prints the state in the form shown below.
#    - `validMoves(state)`: returns list of moves that are valid from `state`.
#    - `makeMove(state, move)`: returns new (copy of) state after move has been applied.
#    - `trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF)`: train the Q function for number of repetitions, decaying epsilon at start of each repetition. Returns Q and list or array of number of steps to reach goal for each repetition.
#    - `testQ(Q, maxSteps, validMovesF, makeMoveF)`: without updating Q, use Q to find greedy action each step until goal is found. Return path of states.
#    - `stateMoveTuple(state, move)`: returns tuple of state and move.

# In[1]:

from copy import deepcopy
import numpy as np
import matplotlib.pyplot as plt
get_ipython().magic('matplotlib inline')
from IPython.display import display, clear_output


# **`printState(state)`**: prints the state in the form shown below.

# In[2]:

def printState(state):
    #Check for the three conditions: peg has 3 disks, peg has 2 and one has 1, each peg has 3 disks
    unique = True
    for i in range(3):
        currPeg = state[i]
        if len(currPeg) is 3:
            if i is 0:
                print(str(currPeg[0]) + "\n" + str(currPeg[1]) + "\n" + str(currPeg[2]) + "\n------")
            elif i is 1:
                print("  " + str(currPeg[0]) + "\n  " + str(currPeg[1]) + "\n  " + str(currPeg[2]) + "\n------")
            else:
                print("    " + str(currPeg[0]) + "\n    " + str(currPeg[1]) + "\n    " + str(currPeg[2]) + "\n------")
            return
        elif len(currPeg) is 2:
            unique = False
            
    #peg has 1 disk:
    if unique:
        for currPeg in state:
            print(currPeg[0], end = " ")
        print("")
    #peg has 2, another has 1:
    else:
        for row in range(2):
            for currPeg in state:
                if len(currPeg) is 2 and row is 0:
                    print(str(currPeg[0]), end = " ")
                elif len(currPeg) is 2:
                    print(str(currPeg[1]), end = " ")
                elif len(currPeg) is 1 and row is 1:
                    print(currPeg[0], end = " ")
                else:
                    print(" ", end = " ")
            print("")
    print("------")  


# printState(state) tests:

# In[3]:

state = [[1, 2, 3], [], []]
printState(state)


# In[4]:

state = [[1], [], [2, 3]]
printState(state)


# In[5]:

state = [[1], [2], [3]]
printState(state)


# In[6]:

state = [[], [1], [2,3]]
printState(state)


# In[7]:

state = [[], [], [1,2,3]]
printState(state)


# **`validMoves(state)`**: returns list of moves that are valid from `state`.

# In[8]:

def validMoves(state):
    moves = []
    for i in range(3):
        currPeg = state[i]
        if len(currPeg) is not 0:
            top = currPeg[0]
            for j in range(3):
                if i == j:
                    continue
                newPeg = state[j]
                if len(newPeg) is 0:
                    moves.append([i+1,j+1])
                else:
                    newTop = newPeg[0]
                    if top < newTop:
                        moves.append([i+1,j+1])
    return moves


# validMoves(state) tests:

# In[9]:

state = [[1, 2, 3], [], []]
validMoves(state)


# In[10]:

state = [[1, 2], [], [3]]
validMoves(state)


# In[11]:

state = [[3, 2], [], [1]]
validMoves(state)


# **`makeMove(state, move)`**: returns new (copy of) state after move has been applied.

# In[12]:

def makeMove(state, move):
    newState = deepcopy(state)
    #Subtract one from each value in move to convert back to index
    iFrom = move[0]-1
    iTo = move[1]-1
    #Always move the top disk, so whatever is at front of list at iFrom
    disk = newState[iFrom][0]
    #Remove disk from iFrom
    newState[iFrom].remove(disk)
    #Add disk to iTo
    newState[iTo].insert(0, disk)
    return newState


# makeMove(state, move) tests:

# In[13]:

state = [[1, 2, 3], [], []]
validMoves(state)


# In[14]:

newState = makeMove(state, [1,2,3])
printState(state)
printState(newState)


# In[15]:

newState = makeMove(state, [1,2])
printState(state)
printState(newState)
state = newState


# In[16]:

validMoves(state)


# In[17]:

newState = makeMove(state, [1,3,2])
printState(state)
printState(newState)


# In[18]:

def stateMoveTuple(state, move):
    first = tuple(state[0])
    second = tuple(state[1])
    third = tuple(state[2])
    tMove = tuple(move)
    SMT = ((first, second, third), tMove)
    return SMT


# stateMoveTuple(state, move) tests:

# In[19]:

state = [[1, 2, 3], [], []]
move =[1, 3]
stateMoveTuple(state, move)


# In[20]:

state = [[1], [2], [3]]
move =[1, 2]
stateMoveTuple(state, move)


# In[21]:

state = [[], [2, 3], [1]]
move =[2, 3]
stateMoveTuple(state, move)


# ## Q Table

# The following functions initialize the Q table, creates training functions, and creates learning params. These functions are all based off of example code given in class.

# In[85]:

def epsilonGreedy(epsilon, Q, state, validMovesF):
    posMoves = validMovesF(state)
    if np.random.uniform() < epsilon:
        rand = np.random.randint(len(posMoves)-1)
        return posMoves[rand]
    else:
        Qs = np.array([Q.get(stateMoveTuple(state, m), 0) for m in posMoves]) 
        return posMoves[np.argmin(Qs)]


# Training Functions:

# In[86]:

epsilonDecayFactor = 0.99
learningRate = 0.25
nRepetitions = 50000


# In[87]:

def plotOutcomes(numSteps, nRepetitions, rep):
    if rep==0:
        return
    nBins = 100
    nPer = int(nRepetitions/nBins)
    
    avgs = [sum(numSteps[i:i+nPer])//nPer for i in range(0, len(numSteps), nPer)]
    if len(avgs) > 2:
        avgs.pop()
        avgs.append(avgs[-1])
    
    plt.subplot(1,1,1) 
    xs = np.linspace(nPer,rep,len(avgs))
    plt.plot(xs, avgs)
    plt.xlabel('Repetitions')
    plt.ylabel('Mean of Number of Steps \nto Solution (ideal is 7)')
    plt.title('Bins of {:d} Repetitions'.format(nPer))
    plt.axhline(y=7, color = 'r', linestyle='--')


# **`trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF)`**: train the Q function for number of repetitions, decaying epsilon at start of each repetition. Returns Q and list or array of number of steps to reach goal for each repetition.

# In[88]:

def trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF):
    Q = {}
    numSteps = []
    epsilon = 1.0
    # this needs to be set to true in order to see the charts plotted
    graphics = False
    if graphics:
        fig = plt.figure(figsize=(10,10))
    
    for rep in range(nRepetitions):
        epsilon *= epsilonDecayFactor
        step = 0
        state = [[1,2,3],[],[]]
        done = False
        
        while not done:
            step += 1
            #find next move:
            move = epsilonGreedy(epsilon, Q, state, validMovesF)
            #take next move:
            newS = makeMoveF(state, move)
            #add to Q table
            currSMT = stateMoveTuple(state,move)
            if currSMT not in Q:
                Q[currSMT] = 0
            
            if step > 1:
                prevSMT = stateMoveTuple(oldS, oldM)
                #check if puzzle has been solved:
                if newS == [[],[],[1,2,3]]:
                    done = True
                    Q[prevSMT] = 1
                    numSteps.append(step)
                else:  
                    Q[prevSMT] += learningRate * (1 + Q[currSMT] - Q[prevSMT])
            
            oldS, oldM = state, move 
            state = newS
    
        if graphics and (rep % (nRepetitions/10) == 0 or rep == nRepetitions-1):
            fig.clf()
            plotOutcomes(numSteps,nRepetitions,rep-1)
            clear_output(wait=True)
            display(fig);
        
    if graphics:
        clear_output(wait=True)
    return Q, numSteps


# `plotOutcomes(numSteps, nRepetitions, rep)` and `trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF)` tests:

# **NOTE:** In order to plot the charts I suggest to comment out the return of trainQ and set the graphics boolean to true in order to properly see what I am commenting on in the markdown. But leaving the graphics boolean true breaks the auto grader, sorry for the inconvience.

# In[45]:

epsilonDecayFactor = 0.99
learningRate = 0.25 #same as rho
nRepetitions = 30000
graphics = True
trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMoves, makeMove)


# As you can see from the above charts, with these parameters it converges onto the ideal number of steps pretty quickly. However, if you rerun this multiple times, you will see that it is not consistent; it is just as likely to converge on 8 steps as 7. I believe the learning rate is a little too high.

# In[46]:

epsilonDecayFactor = 0.999
learningRate = 0.10 #same as rho
nRepetitions = 30000
graphics = True
trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMoves, makeMove)


# This seems to perform much better; we can see "hesitation" when the program reaches 8 steps in the solution path, but it is able to continue to find the ideal 7 step solution.

# In[47]:

epsilonDecayFactor = 0.999
learningRate = 0.02 #same as rho
nRepetitions = 30000
graphics = True
trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMoves, makeMove)


# This seems to do just fine as well, very consistent, while still finding the correct solution path very quickly (approximately 10,000 iterations). While there is always more fine-tuning that could be done, these values for `learningRate` and `epsilonDecayFactor` seem to provide very consistent results.

# In[48]:

epsilonDecayFactor = 0.999
learningRate = 0.002 #same as rho
nRepetitions = 30000
graphics = True
trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMoves, makeMove)


# Again, with these values we see that the minimum solution path of 7 is found consistently, in around 10,000 - 15,000 iterations. As we do not see a noticeable increase in consistency over `learningRate = .02` shown above this test, I would prefer the 0.2 value as it decreases the number of iterations necessary while not sacrificing accuracy.  

# # Examples

# In[89]:

def testQ(Q, maxSteps, validMovesF, makeMoveF):
    state = [[1,2,3],[],[]]
    path = []
    step = 0
    while(step <= maxSteps):
        step += 1
        poss = validMovesF(state)
        Qs = np.array([Q.get(stateMoveTuple(state, m), 0) for m in poss])
        nextM = poss[np.argmin(Qs)]
        path.append(nextM)
        state = makeMoveF(state, nextM)
        if state == [[],[],[1,2,3]]:
            return path
    return path   


# `testQ(Q, maxSteps, validMovesF, makeMoveF)` tests:

# In[90]:

Q, steps = trainQ(1000, 0.5, 0.7, validMoves, makeMove)


# In[91]:

path = testQ(Q, 20, validMoves, makeMove)


# In[92]:

path


# **Provided Examples**:

# In[93]:

state = [[1, 2, 3], [], []]
printState(state)


# In[94]:

validMoves(state)


# In[95]:

move =[1, 2]

stateMoveTuple(state, move)


# In[96]:

newstate = makeMove(state, move)
newstate


# In[97]:

printState(newstate)


# In[98]:

Q, stepsToGoal = trainQ(50, 0.5, 0.7, validMoves, makeMove)


# In[99]:

stepsToGoal


# In[100]:

path = testQ(Q, 20, validMoves, makeMove)


# In[101]:

path


# ## Grading

# Download and extract `A4grader.py` from [A4grader.tar](http://www.cs.colostate.edu/~anderson/cs440/notebooks/A4grader.tar).

# In[ ]:

get_ipython().magic('run -i A4grader.py')


# coding: utf-8

# # Reinforcement Learning Solution to the Towers of Hanoi Puzzle

# For this assignment, you will use reinforcement learning to solve the [Towers of Hanoi](https://en.wikipedia.org/wiki/Tower_of_Hanoi) puzzle.  
# 
# To accomplish this, you must modify the code discussed in lecture for learning to play Tic-Tac-Toe.  Modify the code  so that it learns to solve the three-disk, three-peg
# Towers of Hanoi Puzzle.  In some ways, this will be simpler than the
# Tic-Tac-Toe code.  
# 
# Steps required to do this include the following:
# 
#   - Represent the state, and use it as a tuple as a key to the Q dictionary.
#   - Make sure only valid moves are tried from each state.
#   - Assign reinforcement of $1$ to each move, even for the move that results in the goal state.
# 
# Make a plot of the number of steps required to reach the goal for each
# trial.  Each trial starts from the same initial state.  Decay epsilon
# as in the Tic-Tac-Toe code.

# ## Requirements

# First, how should we represent the state of this puzzle?  We need to keep track of which disks are on which pegs. Name the disks 1, 2, and 3, with 1 being the smallest disk and 3 being the largest. The set of disks on a peg can be represented as a list of integers.  Then the state can be a list of three lists.
# 
# For example, the starting state with all disks being on the left peg would be `[[1, 2, 3], [], []]`.  After moving disk 1 to peg 2, we have `[[2, 3], [1], []]`.
# 
# To represent that move we just made, we can use a list of two peg numbers, like `[1, 2]`, representing a move of the top disk on peg 1 to peg 2.

# Now on to some functions. Define at least the following functions. Examples showing required output appear below.
# 
#    - `printState(state)`: prints the state in the form shown below
#    - `validMoves(state)`: returns list of moves that are valid from `state`
#    - `makeMove(state, move)`: returns new (copy of) state after move has been applied.
#    - `trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF)`: train the Q function for number of repetitions, decaying epsilon at start of each repetition. Returns Q and list or array of number of steps to reach goal for each repetition.
#    - `testQ(Q, maxSteps, validMovesF, makeMoveF)`: without updating Q, use Q to find greedy action each step until goal is found. Return path of states.
# 
# A function that you might choose to implement is
# 
#    - `stateMoveTuple(state, move)`: returns tuple of state and move.  
#     
# This is useful for converting state and move to a key to be used for the Q dictionary.
# 
# Show the code and results for testing each function.  Then experiment with various values of `nRepetitions`, `learningRate`, and `epsilonDecayFactor` to find values that work reasonably well, meaning that eventually the minimum solution path of seven steps is found consistently.
# 
# Make a plot of the number of steps in the solution path versus number of repetitions. The plot should clearly show the number of steps in the solution path eventually reaching the minimum of seven steps, though the decrease will not be monotonic.  Also plot a horizontal, dashed line at 7 to show the optimal path length.
# 
# Add markdown cells in which you describe the Q learning algorithm and your implementation of Q learning as applied to the Towers of Hanoi problem.  Use at least 15 sentences, in one or more markdown cells.

# ## Towers of Hanoi Helper Functions

# These functions below are specific to the Towers of Hanoi puzzle, a description of which can be found [here](https://en.wikipedia.org/wiki/Tower_of_Hanoi). The functions are generally summarized as follows:
# 
#    - `printState(state)`: prints the state in the form shown below
#    - `validMoves(state)`: returns list of moves that are valid from `state`
#    - `makeMove(state, move)`: returns new (copy of) state after move has been applied.
#    - `trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF)`: train the Q function for number of repetitions, decaying epsilon at start of each repetition. Returns Q and list or array of number of steps to reach goal for each repetition.
#    - `testQ(Q, maxSteps, validMovesF, makeMoveF)`: without updating Q, use Q to find greedy action each step until goal is found. Return path of states.
#    - `stateMoveTuple(state, move)`: returns tuple of state and move.
# 
# *note: these function definitions were copied from the CS440 A4 assignment page located [here](http://nbviewer.jupyter.org/url/www.cs.colostate.edu/~anderson/cs440/notebooks/A4%20Reinforcement%20Learning%20Solution%20to%20Towers%20of%20Hanoi.ipynb).*
# 
# I've also added some additional comments when it seemed necessary, as well as some preliminary testing below each function. 

# In[3]:

from copy import deepcopy
import numpy as np
import matplotlib.pyplot as plt
get_ipython().magic('matplotlib inline')
from IPython.display import display, clear_output


# In[4]:

def printState(state):
    #three conditions to check. One peg has three disks, one peg has 2 and another has 1, or each peg has 3 disks.
    oneEach = True
    for i in range(3):
        peg = state[i]
        if len(peg) is 3:
            if i is 0:
                print(str(peg[0]) + "\n" + str(peg[1]) + "\n" + str(peg[2]) + "\n------")
            elif i is 1:
                print("  " + str(peg[0]) + "\n  " + str(peg[1]) + "\n  " + str(peg[2]) + "\n------")
            else:
                print("    " + str(peg[0]) + "\n    " + str(peg[1]) + "\n    " + str(peg[2]) + "\n------")
            return
        elif len(peg) is 2:
            oneEach = False
    #not the most efficient, but given the small sizes it works ok.
    #at this point, we know the max number of disks on a single peg (either 2 or 1 by now, 3 would have returned already)
    
    #if each peg has a single disk:
    if oneEach:
        for peg in state:
            print(peg[0], end = " ")
        print("")
    #if one peg has 2, another has 1:
    else:
        for row in range(2):
            for peg in state:
                if len(peg) is 2 and row is 0:
                    print(str(peg[0]), end = " ")
                elif len(peg) is 2:
                    print(str(peg[1]), end = " ")
                elif len(peg) is 1 and row is 1:
                    print(peg[0], end = " ")
                else:
                    print(" ", end = " ")
            print("")
    print("------")  


# Testing printState(state) function:

# In[5]:

state = [[1, 2, 3], [], []]
printState(state)


# In[6]:

state = [[], [1], [2, 3]]
printState(state)


# In[7]:

state = [[2], [1], [3]]
printState(state)


# In[8]:

state = [[], [1], [2,3]]
printState(state)


# In[9]:

state = [[], [1,2,3], []]
printState(state)


# Note: inserting moves at end of list here. Could change to append (validMoves)...

# In[10]:

def validMoves(state):
    moves = []
    for i in range(3):
        peg = state[i]
        if len(peg) is not 0:
            topDisk = peg[0]
            for j in range(3):
                if i == j:
                    continue
                newPeg = state[j]
                if len(newPeg) is 0:
                    moves.append([i+1,j+1])
                else:
                    newTopDisk = newPeg[0]
                    if topDisk < newTopDisk:
                        moves.append([i+1,j+1])
    return moves


# Testing validMoves(state) function:

# In[11]:

state = [[1, 2, 3], [], []]
validMoves(state)


# In[12]:

state = [[1, 3], [], [2]]
validMoves(state)


# In[13]:

state = [[2, 3], [1], []]
validMoves(state)


# validMoves(state) passes its preliminary testing, and seems to be functioning as expected.

# In[14]:

def makeMove(state, move):
    newState = deepcopy(state)
    #subtract one from each value in move to convert back to index (as index 0 = peg 1, etc)
    indexFrom = move[0]-1
    indexTo = move[1]-1
    #always move the top disk, so whatever is at front of list at 'indexFrom'
    disk = newState[indexFrom][0]
    #remove disk from 'indexFrom'
    newState[indexFrom].remove(disk)
    #add disk to indexTo (per comments above it is assumed to be a valid move)
    newState[indexTo].insert(0, disk)
    return newState
    


# Testing makeMove(state, move) function:

# In[15]:

state = [[1, 2, 3], [], []]
validMoves(state)


# In[16]:

newState = makeMove(state, [1,2])
printState(state)
printState(newState)


# In[17]:

newState = makeMove(state, [1,3])
printState(state)
printState(newState)
state = newState


# In[18]:

validMoves(state)


# In[19]:

newState = makeMove(state, [3,2])
printState(state)
printState(newState)


# makeMove(state, move) is performing as expected. 

# In[20]:

def stateMoveTuple(state, move):
    first = tuple(state[0])
    second = tuple(state[1])
    third = tuple(state[2])
    tMove = tuple(move)
    sMT = ((first, second, third), tMove)
    return sMT


# Testing stateMoveTuple(state, move) functionality:

# In[21]:

state = [[1, 2, 3], [], []]
move =[1, 2]
stateMoveTuple(state, move)


# In[22]:

state = [[], [2, 3], [1]]
move =[2, 3]
stateMoveTuple(state, move)


# This function passes preliminary testing. I was concerned at the addition of the comma for tuples with a single element (as seen directly above with (1,)). This does appear to be typical for python tuples, however, so I believe this is accurate. I will test further later on.

# ## Q Table

# Now, on to setting up and initializing the Q table, setting learning parameters, and creating the training functions.

# *Note: the following function `epsilonGreedy(epsilon, Q, board)` was adapted from a similar function provided to the class [here](http://nbviewer.jupyter.org/url/www.cs.colostate.edu/~anderson/cs440/notebooks/15%20Reinforcement%20Learning%20for%20Two-Player%20Games.ipynb). It was adapted to work for the Towers of Hanoi.*

# In[23]:

## NOTE: changed argmax in the last line to argmin, as we want to minimize cost of solution

def epsilonGreedy(epsilon, Q, state, validMovesF):
    possibleMoves = validMovesF(state)
    if np.random.uniform() < epsilon:
        rand = np.random.randint(len(possibleMoves)-1)
        return possibleMoves[rand]
    else:
        Qs = np.array([Q.get(stateMoveTuple(state, m), 0) for m in possibleMoves]) 
        return possibleMoves[np.argmin(Qs)]


# Now, for the actual training function! 

# In[24]:

epsilonDecayFactor = 0.99
learningRate = 0.25 #same as rho
nRepetitions = 50000


# In[25]:

def plotOutcomes(numSteps, nRepetitions, rep):
    if rep==0:
        return
    nBins = 100
    nPer = int(nRepetitions/nBins)
    
    avgs = [sum(numSteps[i:i+nPer])//nPer for i in range(0, len(numSteps), nPer)]
    if len(avgs) > 2:
        avgs.pop()
        avgs.append(avgs[-1])
    #basically, need to divide numSteps (list) into a list of averages. The averages come from nPer iterations...
    
    plt.subplot(2,1,1) 
    xs = np.linspace(nPer,rep,len(avgs))
    plt.plot(xs, avgs)
    plt.xlabel('Repetitions')
    plt.ylabel('Mean of Number of Steps \nto Solution (ideal is 7)')
    plt.title('Bins of {:d} Repetitions'.format(nPer))
    plt.axhline(y=7, color = 'r', linestyle='--')
    plt.subplot(2,1,2)
    sum1L = []
    sum2L = []
    sum3L = []
    for i in range(0, len(numSteps), nPer):
        temp = numSteps[i:i+nPer]
        sum1L.append(sum(1 for y in temp if y > 11))
        sum2L.append(sum(1 for y in temp if y < 12 and y > 7))
        sum3L.append(sum(1 for y in temp if y == 7))
    if len(sum1L) > 2:
        sum1L.pop()
        temp = sum1L[-1]
        sum1L.append(sum1L[-1])
        sum2L.pop()
        sum2L.append(sum2L[-1])
        sum3L.pop()
        sum3L.append(sum3L[-1])
    plt.plot(xs,sum1L,'g-',label='Solution paths greater than 11 steps')
    plt.plot(xs,sum2L,'b-',label='Solution paths between 8 to 10 steps')
    plt.plot(xs,sum3L,'r-',label='Solution paths of exactly 7 steps (ideal)')
    plt.legend(loc="center")
    plt.ylabel('Number of Games\nin Bins of {:d}'.format(nPer))
    plt.xlabel('Repetitions')


# In[39]:

def trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF):
    Q = {}
    numSteps = []    #keep track of the number of steps to solve the puzzle for each iteration (ideal is 7)
    epsilon = 1.0
    graphics = True
    if graphics:
        fig = plt.figure(figsize=(10,10))
    
    for rep in range(nRepetitions):
        epsilon *= epsilonDecayFactor
        step = 0
        state = [[1,2,3],[],[]]
        done = False
        
        while not done:
            step += 1
            #find next move:
            move = epsilonGreedy(epsilon, Q, state, validMovesF)
            #take next move:
            newState = makeMoveF(state, move)
            #add to Q table
            newSMT = stateMoveTuple(state,move)
            if newSMT not in Q:
                Q[newSMT] = 0     # initial value is 0
            
            if step > 1:
                oldSMT = stateMoveTuple(oldState, oldMove)
                #check if puzzle has been solved:
                if newState == [[],[],[1,2,3]]:
                    done = True
                    Q[oldSMT] = 1
                    numSteps.append(step)
                else:  
                    Q[oldSMT] += learningRate * (1 + Q[newSMT] - Q[oldSMT])
            
            oldState, oldMove = state, move 
            state = newState
    
        if graphics and (rep % (nRepetitions/10) == 0 or rep == nRepetitions-1):
            fig.clf()
            plotOutcomes(numSteps,nRepetitions,rep-1)
            clear_output(wait=True)
            display(fig);
        
    if graphics:
        clear_output(wait=True)
  #  return Q, numSteps


# Now, preliminary testing for both `plotOutcomes(numSteps, nRepetitions, rep)` and `trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF)`:

# In[40]:

epsilonDecayFactor = 0.99
learningRate = 0.25 #same as rho
nRepetitions = 30000
graphics = True
trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMoves, makeMove)


# As you can see from the above charts, with these parameters it converges onto the ideal number of steps pretty quickly. However, if you rerun this multiple times, you will see that it is not consistent; it is just as likely to converge on 8 steps as 7. I believe the learning rate is a little too high.

# In[41]:

epsilonDecayFactor = 0.999
learningRate = 0.10 #same as rho
nRepetitions = 30000
graphics = True
trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMoves, makeMove)


# This seems to perform much better; we can see "hesitation" when the program reaches 8 steps in the solution path, but it is able to continue to find the ideal 7 step solution.

# In[42]:

epsilonDecayFactor = 0.999
learningRate = 0.02 #same as rho
nRepetitions = 30000
graphics = True
trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMoves, makeMove)


# This seems to do just fine as well, very consistent, while still finding the correct solution path very quickly (approximately 10,000 iterations). While there is always more fine-tuning that could be done, these values for `learningRate` and `epsilonDecayFactor` seem to provide very consistent results.

# In[43]:

epsilonDecayFactor = 0.999
learningRate = 0.002 #same as rho
nRepetitions = 30000
graphics = True
trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMoves, makeMove)


# Again, with these values we see that the minimum solution path of 7 is found consistently, in around 10,000 - 15,000 iterations. As we do not see a noticeable increase in consistency over `learningRate = .02` shown above this test, I would prefer the 0.2 value as it decreases the number of iterations necessary while not sacrificing accuracy.  

# # Examples

# In[44]:

state = [[1, 2, 3], [], []]
printState(state)


# In[45]:

validMoves(state)


# In[46]:

move =[1, 2]

stateMoveTuple(state, move)


# In[47]:

newstate = makeMove(state, move)
newstate


# In[48]:

printState(newstate)


# In[49]:

Q, stepsToGoal = trainQ(50, 0.5, 0.7, validMoves, makeMove)


# In[ ]:

stepsToGoal


# In[ ]:

path = testQ(Q, 20, validMoves, makeMove)


# In[ ]:

path


# In[ ]:

for s in path:
    printState(s)
    print()


# ## Grading

# Download and extract `A4grader.py` from [A4grader.tar](http://www.cs.colostate.edu/~anderson/cs440/notebooks/A4grader.tar).

# In[194]:

get_ipython().magic('run -i A4grader.py')


# ## Extra Credit

# Modify your code to solve the Towers of Hanoi puzzle with 4 disks instead of 3.  Name your functions
# 
#     - printState_4disk
#     - validMoves_4disk
#     - makeMove_4disk
# 
# Find values for number of repetitions, learning rate, and epsilon decay factor for which trainQ learns a Q function that testQ can use to find the shortest solution path.  Include the output from the successful calls to trainQ and testQ.
