
# coding: utf-8

# # Assignment 2: Iterative-Deepening Search

# *Luke Burford*

# ## Overview

# Implement the iterative-deepening search algorithm as discussed in our Week 2 lecture notes and as shown in figures 3.17 and 3.18 in our text book. Apply it to the 8-puzzle and a second puzzle of your choice. 

# ## Required Code

# In this jupyter notebook, implement the following functions:
# 
#   * `iterativeDeepeningSearch(startState, goalState, actionsF, takeActionF, maxDepth)`
#   * `depthLimitedSearch(startState, goalState, actionsF, takeActionF, depthLimit)`
#   
# `depthLimitedSearch` is called by `iterativeDeepeningSearch` with `depthLimit`s of $0, 1, \ldots, $ `maxDepth`. Both must return either the solution path as a list of states, or the strings `cutoff` or `failure`.  `failure` signifies that all states were searched and the goal was not found. 
# 
# Each receives the arguments
# 
#   * the starting state, 
#   * the goal state,
#   * a function `actionsF` that is given a state and returns a list of valid actions from that state,
#   * a function `takeActionF` that is given a state and an action and returns the new state that results from applying the action to the state,
#   * either a `depthLimit` for `depthLimitedSearch`, or `maxDepth` for `iterativeDeepeningSearch`.

# Use your solution to solve the 8-puzzle.
# Implement the state of the puzzle as a list of integers. 0 represents the empty position. 
# 
# Required functions for the 8-puzzle are the following.
# 
#   * `findBlank_8p(state)`: return the row and column index for the location of the blank (the 0 value).
#   * `actionsF_8p(state)`: returns a list of up to four valid actions that can be applied in `state`. Return them in the order `left`, `right`, `up`, `down`, though only if each one is a valid action.
#   * `takeActionF_8p(state, action)`: return the state that results from applying `action` in `state`.
#   * `printPath_8p(startState, goalState, path)`: print a solution path in a readable form.  You choose the format.

# <font color='red'>Also</font>, implement a second search problem of your choice.  Apply your `iterativeDeepeningSearch` function to it.

# Insert your function definitions in this notebook.

# depthLimitedSearch Function

# In[315]:

# from A2mysolution import *
def depthLimitedSearch(state, goalState, actionsF, takeActionF, depthLimit):
    if state == goalState:
        return []
    if depthLimit is 0:
        return'cutoff' # the string to signal that the depth limit was reached
    cutoffOccurred = False
    for action in actionsF(state):
        childState = takeActionF(state, action)
        result = depthLimitedSearch(childState, goalState, actionsF, takeActionF, depthLimit-1)
        if result is 'cutoff':
            cutoffOccurred = True
        elif result is not 'failure':
            #Add childState to front of partial solution path, in result, returned by depthLimitedSearch
            result.insert(0, childState)
            return result
    if cutoffOccurred:
        return 'cutoff'
    else:
        return 'failure'


# IterativeDeepeningSearch Function

# In[316]:

def iterativeDeepeningSearch(startState, goalState, actionsF, takeActionF, maxDepth):
    for depth in range(maxDepth):
        result = depthLimitedSearch(startState, goalState, actionsF, takeActionF, depth)
        if result is 'failure':
            return 'failure'
        if result is not 'cutoff':
            #Add startState to front of solution path, in result, returned by depthLimitedSearch
            result.insert(0, startState)
            return result
    return 'cutoff'


# Additional Helper Functions

# In[331]:

# Return the row and column index for the location of the blank (the 0 value).
def findBlank_8p(state):
    # get the index of the empty space in the array
    i = state.index(0)
    # brute force solution
    if i < 3:
        return (0, i%3)
    elif i < 6:
        return (1, i%3)
    else:
        return (2, i%3)

# Returns a list of up to four valid actions that can be applied in state.
# Return them in the order left, right, up, down, though only if each one is a valid 

def actionsF_8p(state):
    actions = []
    state = findBlank_8p(state)
    if state[1] < 2:
        actions.append("left")
    if state[1] > 0:
        actions.append("right")
    if state[0] < 2:
        actions.append("down")
    if state[0] > 0:
        actions.append("up")
    return actions

# Return the state that results from applying action in state.
def takeActionF_8p(state, action):
    if action not in actionsF_8p(state):
        return state
    nState = state.copy()
    i = nState.index(0) # get the index of the blank
    if action is 'left':
        j = i+1 # index of the item to be swapped with
        nState[j], nState[i] = nState[i], nState[j] # swap there indexs
    if action is 'right':
        j = i-1 # index of the item to be swapped with
        nState[j], nState[i] = nState[i], nState[j] # swap there indexs
    if action is 'down':
        j = i+3 # index of the item to be swapped with
        nState[j], nState[i] = nState[i], nState[j] # swap there indexs
    if action is 'up':
        j = i-3 # index of the item to be swapped with
        nState[j], nState[i] = nState[i], nState[j] # swap there indexs
    return nState

# Print a solution path in a readable form. You choose the format.
def printPath_8p(startState, goalState, path):
    print

def printState_8p(startState):
    j = 0
    for i in range(len(startState)):
        j += 1
        print (startState[i], end=" ")
        if j == 3:
            j = 0
            print("\n",end="")


# Here are some example results.

# In[332]:

startState = [1, 0, 3, 4, 2, 5, 6, 7, 8]


# In[333]:

printState_8p(startState)  # not a required function for this assignment, but it helps when implementing printPath_8p


# In[334]:

findBlank_8p(startState)


# In[335]:

actionsF_8p(startState)


# In[336]:

takeActionF_8p(startState, 'down')


# In[337]:

printState_8p(takeActionF_8p(startState, 'down'))


# In[338]:

goalState = takeActionF_8p(startState, 'down')


# In[339]:

newState = takeActionF_8p(startState, 'down')


# In[340]:

newState == goalState


# In[341]:

startState


# In[342]:

path = depthLimitedSearch(startState, goalState, actionsF_8p, takeActionF_8p, 3)
path


# Notice that `depthLimitedSearch` result is missing the start state.  This is inserted by `iterativeDeepeningSearch`.
# 
# But, when we try `iterativeDeepeningSearch` to do the same search, it finds a shorter path!

# In[343]:

path = iterativeDeepeningSearch(startState, goalState, actionsF_8p, takeActionF_8p, 3)
path


# Also notice that the successor states are lists, not tuples.  This is okay, because the search functions for this assignment do not

# In[344]:

startState = [4, 7, 2, 1, 6, 5, 0, 3, 8]
path = iterativeDeepeningSearch(startState, goalState, actionsF_8p, takeActionF_8p, 3)
path


# In[345]:

startState = [4, 7, 2, 1, 6, 5, 0, 3, 8]
path = iterativeDeepeningSearch(startState, goalState, actionsF_8p, takeActionF_8p, 5)
path


# Humm...maybe we can't reach the goal state from this state.  We need a way to randomly generate a valid start state.

# In[346]:

import random


# In[347]:

random.choice(['left', 'right'])


# In[348]:

def randomStartState(goalState, actionsF, takeActionF, nSteps):
    state = goalState
    for i in range(nSteps):
        state = takeActionF(state, random.choice(actionsF(state)))
    return state


# In[349]:

goalState = [1, 2, 3, 4, 0, 5, 6, 7, 8]
randomStartState(goalState, actionsF_8p, takeActionF_8p, 10)


# In[350]:

startState = randomStartState(goalState, actionsF_8p, takeActionF_8p, 50)
startState


# In[351]:

path = iterativeDeepeningSearch(startState, goalState, actionsF_8p, takeActionF_8p, 20)
path


# Let's print out the state sequence in a readable form.

# In[352]:

for p in path:
    printState_8p(p)
    print()


# Here is one way to format the search problem and solution in a readable form.

# In[353]:

printPath_8p(startState, goalState, path)


# Download [A2grader.tar](A2grader.tar) and extract A2grader.py from it.

# In[ ]:

get_ipython().magic('run -i A2grader.py')


# In[286]:

state = [1, 2, 3, 4, 5, 6, 7, 0, 8]


# In[287]:

printState_8p(state)


# In[288]:

findBlank_8p(state)


# ## Extra Credit
# 
# For extra credit, apply your solution to the grid example in Assignment 1 with the addition of a horizontal and vertical barrier at least three positions long.  Demonstrate the solutions found in four different pairs of start and goal states.
