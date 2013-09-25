
print "Testing if compilation of functions in nquad will speed up the execution of the integration"

from timetest import *


timeTest('oneD', '[[-1,1]]', "3")
timeTest("twoD", "[[-200, -0.5], [-1,1]]")

timeTest("threeD", "[[-19,87],[0,1],[0,3.14]]")
#timeTest("fourD", "[[0,1],[-1,1],[.13,.8],[-.15,1]]") timetest does not yet support functions with extra arguments

#timeTest("fiveD", "[[-19,12],[10,11],[-1,4],[0,6],[9,0]]")

timeTest("threeDOsc", "[[-2.5,2.5],[1,6], [0,2]]", "1")

timeTest("oneDOsc", "[[-3.1415926,3.1415926]]", "1000")

''' 
print ""
print "Example function from nquad documentation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
print "Python"
print "Solution = "
print integrate.nquad(fourDPython, [[0,1], [-1,1], [.13,.8], [-.15,1]],opts=[opts0,{},{},{}])
print "Time = "
print timeit.timeit('integrate.nquad(fourDPython, [[0,1], [-1,1], [.13,.8], [-.15,1]],opts=[opts0,{},{},{}])', 'from scipy import integrate ; from __main__ import fourDPython ; from __main__ import opts0', number=1)
print "Fortran"
print "Solution = "
print integrate.nquad(comp.fourdcompiled, [[0,1], [-1,1], [.13,.8], [-.15,1]],opts=[opts0,{},{},{}]) #The fortran function actually stores a temp value instead of the if else statement in python.  This may use more space computationally or be slightly slower.  I'm not sure if theres another way I can write it.
print "Time = "
print timeit.timeit('integrate.nquad(comp.fourdcompiled, [[0,1],[-1,1],[.13,.8], [-.15,1]],opts=[opts0, {},{},{}])', 'from scipy import integrate ; import comp ; from __main__ import opts0', number=1)
'''
