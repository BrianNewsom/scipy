from ctypes import *
from scipy.integrate import quad
testlib = CDLL('./testlib.so')
testlib.oneD.restype = c_double
testlib.oneD.argtypes = (c_double,)
testlib.twoD.restype = c_double
testlib.twoD.argtypes = (c_double, c_double)
import pdb;pdb.set_trace()
print quad(testlib.oneD,-1,1)
print quad(testlib.twoD,-1,1,(0,))
