
# coding: utf-8

# # Assignment 1: Uninformed Search

# Luke Burford

# ## Overview

# Breadth-first and depth-first are two algorithms for performing
# uninformed search---a search that does not use
# knowledge about the goal of the search.  You will implement both
# search algorithms in python and test them on a simple graph.  Then you
# will apply your search algorithms to a puzzle problem of your choice
# as explained below.

# ## Required Code

# In this jupyter notebook, you must implement at least the following functions:
# 
#   * `breadthFirstSearch(startState, goalState, successorsf)` 
#   * `depthFirstSearch(startState, goalState, successorsf)`
#   
# Each receives as arguments the starting state, the goal state, and a successors function.  `breadthFirstSearch` returns the breadth-first solution path as a list of states starting with the `startState` and ending with the `goalState`.  `depthFirstSearch` returns the depth-first solution path.
# 
# Demonstrate each one running with a simple graph as shown in the following example, and with the grid example.  Test your code on other graphs, which <font color="green">MAY CONTAIN CYCLES.  Grading will be based on search problem examples different from the simple graph and grid example shown here.</font>

# If you prefer to develop your python code in a separate editor or IDE, you may do so.  If it is stored in a file called `A1mysolution.py`, you can use it here by executing the following cell.
# 
# When your solution works, <font color="red">REMEMBER</font> to remove or comment out the following import statement and instead, paste in all of your function definintions into this notebook.

# In[85]:

# from A1mysolution import *
def breadthFirstSearch(startState, goalState, successorsf):
    expanded = {}
    unExpanded = [(startState, None)]
    path = []
    if startState == goalState:
        return startState
    while unExpanded:
        state = unExpanded.pop()
        expanded[state[0]] = state[1]
        children = successorsf(state[0])
        for child in children:
            if child in expanded or child in unExpanded:
                children.remove(child)
            if child == goalState:
                path.append(state[0])
                path.append(goalState)
                parent = state[1]
                while parent:
                    path.insert(0,parent)
                    parent = expanded[parent]
                return path
        children.sort()
        [ unExpanded.insert(0, (child, state[0])) for child in children ]
    return str("Goal not found")
        

def depthFirstSearch(startState, goalState, successorsf):
    expanded = {}
    unExpanded = [(startState, None)]
    path = []
    if startState == goalState:
        return startState
    while unExpanded:
        state = unExpanded.pop()
        expanded[state[0]] = state[1]
        children = successorsf(state[0])
        for child in children:
            if child in expanded or child in unExpanded:
                children.remove(child)
            if child == goalState:
                path.append(state[0])
                path.append(goalState)
                parent = state[1]
                while parent:
                    path.insert(0,parent)
                    parent = expanded[parent]
                return path
        children.sort(reverse = True)
        [ unExpanded.append((child, state[0])) for child in children ]
    return str("Goal not found")


# # Example

# Here is a simple example.  States are defined by lower case letters.  A dictionary stores a list of successor states for each state in the graph that has successors.

# In[86]:

successors = {'a':  ['b', 'c', 'd'],
              'b':  ['e', 'f', 'g'],
              'c':  ['a', 'h', 'i'],
              'd':  ['j', 'z'],
              'e':  ['k', 'l'],
              'g':  ['m'],
              'k':  ['z']}
successors


# In[87]:

import copy

def successorsf(state):
    return copy.copy(successors.get(state, []))


# In[88]:

successorsf('e')


# In[89]:

print('Breadth-first')
print('path from a to a is', breadthFirstSearch('a', 'a', successorsf))
print('path from a to m is', breadthFirstSearch('a', 'm', successorsf))
print('path from a to z is', breadthFirstSearch('a', 'z', successorsf))


# In[90]:

print('Depth-first')
print('path from a to a is', depthFirstSearch('a', 'a', successorsf))
print('path from a to m is', depthFirstSearch('a', 'm', successorsf))
print('path from a to z is', depthFirstSearch('a', 'z', successorsf))


# Let's try a navigation problem around a grid of size 10 x 10. Rows and columns will be indexed from 0 to 9.
# 
# The following function takes the input state and returns all possible states.

# In[13]:

def gridSuccessors(state):
    row, col = state
    # succs will be list of tuples () rather than list of lists [] because state must
    # be an immutable type to serve as a key in dictionary of expanded nodes
    succs = []
    for r in [-1, 0, 1]:   #check each row
        for c in [-1, 0, 1]:  # check in each col
            newr = row + r
            newc = col + c
            if 0 <= newr <= 9 and 0 <= newc <= 9:  
                succs.append( (newr, newc) )
    return succs


# In[14]:

gridSuccessors([3,4])


# In[15]:

gridSuccessors([3,9])


# In[16]:

gridSuccessors([0,0])


# In[17]:

print('Breadth-first')
print('path from (0, 0) to (9, 9) is', breadthFirstSearch((0, 0), (9, 9), gridSuccessors))


# In[18]:

print('Depth-first')
print('path from (0, 0) to (9, 9) is', depthFirstSearch((0, 0), (9, 9), gridSuccessors))


# Let's plot the paths.

# In[19]:

path = depthFirstSearch((0, 0), (9, 9), gridSuccessors)
path


# Now, we have the path to goal state. To plot this path we must extract the first value in each tuple and put them in a list called `rows` to use as the $y$ coordinate of each point, and build a second list called `cols` of second values.

# In[21]:

import matplotlib.pyplot as plt
get_ipython().magic('matplotlib inline')


# In[22]:

rows = [location[0] for location in path]
cols = [location[1] for location in path]
plt.plot(rows,cols,'o-');


# In[23]:

path = breadthFirstSearch((0, 0), (9, 9), gridSuccessors)
print(path)
rows = [location[0] for location in path]
cols = [location[1] for location in path]
plt.plot(rows,cols,'o-');


# In[24]:

depthFirstSearch((0, 0), (9, 20), gridSuccessors)


# # Extra Credit
# 
# For extra credit, use your functions to solve the Camels Puzzle, described at [Logic Puzzles](http://www.folj.com/puzzles/).
# The following code illustrates one possible state representation and shows results of a breadth-first and a dept-first search.  You must define a new successors function, called `camelSuccessorsf`. 

# In[7]:

camelStartState


# In[8]:

camelGoalState


# In[9]:

camelSuccessorsf(camelStartState)


# In[10]:

children = camelSuccessorsf(camelStartState)
print(children[0])
camelSuccessorsf(children[0])


# In[11]:

bfs = breadthFirstSearch(camelStartState, camelGoalState, camelSuccessorsf)
print('Breadth-first solution: (', len(bfs), 'steps)')
for s in bfs:
    print(s)

dfs = depthFirstSearch(camelStartState, camelGoalState, camelSuccessorsf)
print('Depth-first solution: (', len(dfs), 'steps)')
for s in dfs:
    print(s)


# ## Grading
# 
# Your notebook will be run and graded automatically. Download [A1grader.tar](http://www.cs.colostate.edu/~anderson/cs440/notebooks/A1grader.tar)  and extract A1grader.py from it. Run the code in the following cell to demonstrate an example grading session. You should see a perfect score of 80/80 if your functions are defined correctly. 
# 
# The remaining 20% will be based on your writing.  In markdown cells, explain what your functions are doing and make observations about your results.  Also mention problems you encountered in trying to solve this assignment.

# ## Check-in

# Do not include this section in your notebook.
# 
# Name your notebook ```Lastname-A1.ipynb```.  So, for me it would be ```Anderson-A1.ipynb```.  Submit the file using the ```Assignment 1``` link on [Canvas](https://colostate.instructure.com/courses/68135).
# 
# Grading will be based on 
# 
#   * correct behavior of the required functions, and
#   * readability of the notebook.

# In[21]:

get_ipython().magic('run -i A1grader.py')

