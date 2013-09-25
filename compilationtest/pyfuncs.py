import numpy

def oneDPython(x):
    return x+2

def twoDPython(x,y):
    return x**2+y**2

def threeDPython(x,y,z):
    return 12*x**7*y**2*numpy.sin(2*z) + 13

#fourDPython = lambda x0,x1,x2,x3 : x0**2 + x1*x2 - x3**3 + numpy.sin(x0) + (1 if (x0-.2*x3-.5-.25*x1>0) else 0)

points = [[lambda (x1,x2,x3) : 0.2*x3 + 0.5 + 0.25*x1], [], [], []]

def opts0(*args, **kwargs):
    return {'points':[0.2*args[2] + 0.5 + 0.25*args[0]]}

def fourDPython(x0,x1,x2,x3):
    return x0**2 + x1*x2 - x3**3 + numpy.sin(x0) + (1 if (x0-.2*x3-.5-.25*x1>0) else 0)

def fiveDPython(x,y,z,s,t):
    return x*y**z + x*s**t - x*y*z*s*t + 13*s**t

def threeDOscPython(x,y,z):
    return numpy.sin(x) + numpy.sin(y)*numpy.cos(z) + 14*x*y*z

def oneDOscPython(x):
    return numpy.sin(x)
