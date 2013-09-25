!Program made up of compiled functions of 1,2, and 3 variables
!To be compiled by f2py in driver test file
program fortranFns

!print *, 'oneDCompiled(2): (should be 4)', oneDCompiled(2.0)
print *, 'success'

end program


Real(8) function oneDCompiled(x) !Simple 1 d function compiled to fortran
  Real(8) x
!f2py intent(in) x
!f2py intent(out) oneDCompiled
  oneDCompiled = x+2
  return
end function

Real(8) function oneDOscCompiled(x) !Simple 1 d function compiled to fortran
  Real(8) x
!f2py intent(in) x
!f2py intent(out) oneDCompiled
  oneDOscCompiled = sin(x)
  return
end function


Real(8) function twoDCompiled(x,y) !Two dimensional integral 
  Real(8) x
  Real(8) y
!f2py intent(in) x 
!f2py intent(in) y
!f2py intent(out) twoDCompiled
  twoDCompiled = x**2+y**2
  return
end function


Real(8) function threeDCompiled(x,y,z)
  Real(8) x
  Real(8) y
  Real(8) z
!f2py intent(in) x
!f2py intent(in) y
!f2py intent(in) z
!f2py intent(out) threeDCompiled
  threeDCompiled = 12 * x**7 * y**2 * sin(2*z) + 13
  return
end function

Real(8) function fourDCompiled(x0,x1,x2,x3)
  Real(8) x0
  Real(8) x1
  Real(8) x2
  Real(8) x3
  Real temp
  
  if (x0-.2*x3-.5-.25*x1 > 0) then   
     temp = 1
  else
     temp = 0
  endif

  fourDCompiled = x0**2 + x1*x2 - x3**3 + sin(x0) + temp
  return

end function


Real(8) function fiveDCompiled(x,y,z,s,t)
  Real(8) x
  Real(8) y
  Real(8) z
  Real(8) s
  Real(8) t
  fiveDCompiled = x*y**z + x*s**t - x*y*z*s*t + 13*s**t
  return
end function

Real(8) function threeDOscCompiled(x,y,z)
  Real(8) x
  Real(8) y
  Real(8) z
!f2py intent(in) x                                                                                                                          
!f2py intent(in) y                                                                                                                          
!f2py intent(in) z                                                                                                                          
!f2py intent(out) threeDCompiled                                                                                                            
  threeDOscCompiled = sin(x) + sin(y)*cos(z) + 14*x*y*z
  return
end function
