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
    return x**2+y**2+4

#source = 
#ONE D
print "X+2 evaluated from -1, 1"
print "    One dimensional integral, function in python"
print integrate.nquad(oneDPython, [[-1,1]])
print "    One dimensional integral, function in fortran"
print integrate.nquad(comp.onedcompiled, [[-1,1]])

print ""
print "X^2 + Y^2 evaluated from x = -200, -0.5, y = -1,1 "
print "    Two dimensional integral, function in python"
print integrate.nquad(twoDPython, [[-200, -0.5], [1,-1]])
print "    Two dimensional integral, function in fortran"
print integrate.nquad(comp.twodcompiled, [[-200, -0.5], [-1,1]])

print ""
print ""
