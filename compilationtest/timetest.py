B'''
To use this test function simply use
from timetest import * 
at the top of your driver file
Also requires pyfuncs.py file and comp.so library compiled from fortran by f2py
'''


import timeit

try:
    from pyfuncs import *
except:
    print "FAILED TO LOAD PYTHON FUNCTIONS FILE"

try:
    from scipy import integrate
except:
    print "FAILED TO LOAD SCIPY"
    SystemExit(0)

#f2py -m comp com.f90 -c CAN I DO THIS HERE

try:
    import comp
except:
    print "COULD NOT IMPORT COMPILED FUNCTIONS FILE"
    SystemExit(0)


def timeTest(fnName, bounds, nIter="1"):
    """
    Description:
    Prints out solutions as determined by python and fortran compiled method, then prints out the time each took to execute fully.  At this point it runs the function twice to time and get the solution but that may change over time
    Inputs:
    fnName = Properly cased (for Python) name of function previously declared to be timed
    bounds = bounds of integration, in order of fn arguments.  Ex: [[a,b],[c,d],[e,f]]
    nIter = number of times test will be run on each method.  Must be a positive integer.  The time output will be the sum of all those times. (This may change). 
    Sample call:
    import timetest
    timeTest("threeD", [[-19,87],[0,1],[0,3.14]], 10)      

    """
    #Convert to strings to manipulate more easily
    bounds = str(bounds)
    nIter = str(nIter) 

    print "~~~~~~~~~~~~~~~~~~~~~~~~~~integrate " + fnName + " from " + bounds + " run " + nIter + " time(s)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

    print "PYTHON" 
    pyTime = "timeit.timeit('print integrate.nquad(" + fnName + "Python," + bounds + ")', 'from __main__ import " + fnName + "Python ; from scipy import integrate', number=" + nIter + ")"#Holds fn to time
    pyTime =  eval(pyTime)
    print "Time to run all iterations (seconds) = " + str(pyTime)

    print "FORTRAN"
    forTime = "timeit.timeit('print integrate.nquad(comp." + fnName.lower() + "compiled," + bounds + ")', 'from __main__ import comp ; " + "from scipy import integrate', number="+ nIter + ")"#Holds fn to time           
    forTime = eval(forTime)
    print "Time to run all iterations (seconds) = " + str(forTime)
    #Ratio calculates speed up of running fortran vs. python
    ratio = pyTime / forTime
    print "Speed-up factor from Python to Fortran: " + str(ratio)
    return ratio
