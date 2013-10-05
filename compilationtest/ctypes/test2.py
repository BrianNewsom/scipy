Bfrom numpy import sqrt, cos, sin, arctan, exp, log, pi, Inf
#from numpy.testing import assert_, TestCase, run_module_suite, dec
from scipy.integrate import *
import sys
import math


import ctypes

from pyfuncs import *

import timeit
#Parse through functions and make them have correct arg and ret types
lib = ctypes.CDLL('libm.so') #Use c std lib to test w/o my functions problems - works
comp = ctypes.CDLL('/home/brian/Dropbox/Research/myscipy/scipy/compilationtest/ctypes/testlib.so') #Load library of c funcs
restype = ctypes.c_double
argtypes = (ctypes.c_double,)
for name in ['sin','cos','tan']:
    func = getattr(lib, name)
    func.restype = restype
    func.argtypes = argtypes


    
def test_typical():
    print nquad(lib.func,[[0,5]])
    print nquad(math.sin,[[0,5]])

'''                                                                                                                                         
timetest.py
To use this test function simply use                                                                                                        
from timetest import *                                                                                                                      
at the top of your driver file                                                                                                              
Also requires pyfuncs.py file and comp.so library compiled from fortran by f2py
                                                          
'''

def init():
    comp = ctypes.CDLL('/home/brian/Dropbox/Research/myscipy/scipy/compilationtest/ctypes/testlib.so') #Load library of c funcs 
    restype = ctypes.c_double
    argtypes = (ctypes.c_double,) 
    for name in ['func']: 
        func = getattr(comp, name)  
        func.restype = restype
        func.argtypes = argtypes

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
#import pyfuncs
#    auxStr = "restype = ctypes.c_double; argtypes = (ctypes.c_double,) ; for name in ['func']: func = getattr(comp, name) ; func.restype = restype; func.argtypes = argtypes"

  #Convert to strings to manipulate more easily                                                                                           
    bounds = str(bounds)
    nIter = str(nIter)

    print "~~~~~~~~~~~~~~~~~~~~~~~~~~integrate " + fnName + " from " + bounds + " run " + nIter + " time(s)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    
    print "PYTHON"
    pyTime = "timeit.timeit('print integrate.nquad(" + fnName + "Python," + bounds + ")', 'from pyfuncs import " + fnName + "Python ; from scipy import integrate', number=" + nIter + ")"#Holds fn to time                                                                              
    print(pyTime)
    pyTime =  eval(pyTime)
    print "Time to run all iterations (seconds) = " + str(pyTime)
    
    print "FORTRAN"
    forTime = "timeit.timeit('print integrate.nquad(comp." + fnName.lower() + "compiled," + bounds + ")', 'from scipy import integrate ; import ctypes', number="+ nIter + ")"#Holds fn to time                                                                       
    forTime = eval(forTime)
    print "Time to run all iterations (seconds) = " + str(forTime)
    #Ratio calculates speed up of running fortran vs. python                                                                                
    ratio = pyTime / forTime
    print "Speed-up factor from Python to Fortran: " + str(ratio)
    return ratio
