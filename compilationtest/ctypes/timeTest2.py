'''
a = stopwatch.Timer()
print "A"
a.stop()
print a.elapsed
'''

global cTotTime
global pyTotTime 

try: 
    import stopwatch
except:
    print "PLEASE INSTALL STOPWATCH PYTHON UTILITY TO RUN"
    SystemExit(0)

try:
    from pyfuncs import *
except:
    print "FAILED TO LOAD PYTHON FUNCTIONS FILE"

try:
    from scipy import integrate
except:
    print "FAILED TO LOAD SCIPY"
    SystemExit(0)

try:
    import ctypes
except:
    print "COULD NOT LOAD CTYPES"
    SystemExit(0)

#f2py -m comp com.f90 -c CAN I DO THIS HERE                                                                                                

def timeTest(fnName, bounds, nIter="1"):
    """                                                                                                                                     
    Description:                                                                                                                            
    Prints out solutions as determined by python and fortran compiled method, then prints out the time each took to execute fully.                                            
    Inputs:                                                                                                                                 

   fnName = Properly cased (for Python) name of function previously declared to be timed                                                   
    bounds = bounds of integration, in order of fn arguments.  Ex: [[a,b],[c,d],[e,f]]                                                     
    nIter = number of times test will be run on each method.  Must be a positive integer.  The time output will be the sum of all those times.

    Sample call:
    import timetest
    timeTest("threeD", [[-19,87],[0,1],[0,3.14]], 10)                                                                                                                      
    """
           
    #CTYPES IMPORTS (should these be outside function?
    comp = ctypes.CDLL('/home/brian/Dropbox/Research/myscipy/scipy/compilationtest/ctypes/testlib.so')
    restype = ctypes.c_double
    argtypes = (ctypes.c_double,) #Change this to array of c_doubles of size dimension
    for name in [fnName]: #Names of functions to parse
        func = getattr(comp, name)
        func.restype = restype
        func.argtypes = argtypes
    
    bounds = str(bounds) #convert to string to manipulate
    nIter = str(nIter)
    print "~~~~~~~~~~~~~~~~~~~~~~~~~~integrate " + fnName + " from " + bounds + " run " + nIter + " time(s)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

    print "PYTHON"
    for i in range(int(nIter)): #for large nIters, ratio is converging to 1.  Is the time of the loop trumping the time of evaluation for large n? C*O(n) ??
        if (i == 0):
            pyTotTime = 0
            pySW = stopwatch.Timer() #start stopwatch on first iter
            pyTime = "integrate.nquad(" + fnName + "Python," + bounds + ")"
            pyTemp = eval(pyTime)
            pySW.stop()
            pyTotTime = pySW.elapsed
            print pyTemp
        #'''elif (i == int(nIter)):
        #    pySW.start()
        #    pyTime = "integrate.nquad(" + fnName + "Python," + bounds + ")"
        #    pyVal = eval(pyTime)
         #   pySW.stop()
         #   ''' #Attempting to add a value check. Can't use one below because it isn't global :(
        else:
            pyTotTime += pySW.elapsed #total time to run all iterations
            pySW = stopwatch.Timer()
            pyTime = "integrate.nquad(" + fnName + "Python," + bounds + ")"
            pyTemp = eval(pyTime)
            pySW.stop()    
            print pyTemp
    print "Time to run all iterations (seconds) = " + str(pyTotTime)
#    pyTime = "timeit.timeit('print integrate.nquad(" + fnName + "Python," + bounds + ")', 'from __main__ import " + fnName + "Python ; from scipy import integrate', number=" + nIter + ")"#Holds fn to time                                                                           
    #pyTime =  eval(pyTime)
    #print "Time to run all iterations (seconds) = " + str(pyTime)

    print "CTYPES"
    for i in range(int(nIter)):
        if (i==0):
            cSW = stopwatch.Timer()
            cTime = "integrate.nquad(comp." + fnName + "," + bounds + ")"
            cTemp = eval(cTime)
            cSW.stop()
            cTotTime = cSW.elapsed
            print cTemp
        else:
            cTotTime += cSW.elapsed
            cSW = stopwatch.Timer()
            cTime = "integrate.nquad(comp." + fnName + "," + bounds + ")"
            cTemp = eval(cTime)
            cSW.stop()
            print cTemp

    print "Time to run all iterations (seconds) = " + str(cTotTime)
    #forTime = "timeit.timeit('print integrate.nquad(comp." + fnName.lower() + "compiled," + bounds + ")', 'from __main__ import comp ; " + "from scipy import integrate', number="+ nIter + ")"#Holds fn to time                                                                       
    #forTime = eval(forTime)
    #print "Time to run all iterations (seconds) = " + str(forTime)
    #Ratio calculates speed up of running fortran vs. python                                                                                
#    if(cVal != pyVal):
#        print "ERROR: VALUES NOT EQUAL"
        
    ratio = pyTotTime / cTotTime
    print "Speed-up factor from Python to CTypes: " + str(ratio)
    return ratio




