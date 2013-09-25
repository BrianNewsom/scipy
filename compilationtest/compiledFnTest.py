import numpy
import cProfile, pstats, StringIO
import timeit


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


print "Testing if compilation of functions in nquad will speed up the execution of the integration"


def oneDPython(x):
    return x+2

def twoDPython(x,y):
    return x**2+y**2

def threeDPython(x,y,z):
    return 12*x**7*y**2*numpy.sin(2*z) + 13

fourDPython = lambda x0,x1,x2,x3 : x0**2 + x1*x2 - x3**3 + numpy.sin(x0) + (1 if (x0-.2*x3-.5-.25*x1>0) else 0)

points = [[lambda (x1,x2,x3) : 0.2*x3 + 0.5 + 0.25*x1], [], [], []]

def opts0(*args, **kwargs):
    return {'points':[0.2*args[2] + 0.5 + 0.25*args[0]]}
#source = 
#ONE D


#pr = cProfile.Profile()
#pr.enable()

def fn1():
    return integrate.nquad(oneDPython, [[-1,1]])

def fn2():
    return integrate.nquad(comp.onedcompiled, [[-1,1]])


print "X+2 evaluated from -1, 1"
print "    One dimensional integral, function in python"
print integrate.nquad(oneDPython, [[-1,1]])
print timeit.timeit('integrate.nquad(oneDPython, [[-1,1]])','from __main__ import oneDPython ; from scipy import integrate', number=1)
#print fn1()
#print timeit.timeit("fn1()", "from __main__ import fn1")
print "    One dimensional integral, function in fortran"
#print integrate.nquad(comp.onedcompiled, [[-1,1]])
#print timeit.timeit("fn2()", "from __main__ import fn2")


print ""
print "X^2 + Y^2 evaluated from x = -200, -0.5, y = -1,1 "
print "    Two dimensional integral, function in python"
print integrate.nquad(twoDPython, [[-200, -0.5], [-1,1]])
print "    Two dimensional integral, function in fortran"
print integrate.nquad(comp.twodcompiled, [[-200, -0.5], [-1,1]])

print ""
print "12*X^7 * Y^2 * sin(2*Z) evaluated from x = -19, 87 y = 0, 1 and z = 0, 3.14"
print "    Three dimensional integral function in python"
print integrate.nquad(threeDPython, [[-19,87],[0,1],[0,3.14]])
print "    Three dimensional integral function in fortran"
print integrate.nquad(comp.threedcompiled, [[-19,87],[0,1],[0,3.14]])

print ""
print "Example function from nquad documentation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~""
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



#pr.disable()
#s = StringIO.StringIO()
#sortby = 'cumulative'
#ps = pstats.Stats(pr, stream=s).sort_stats(sortby)
#ps.print_stats()
#print s.getvalue()
