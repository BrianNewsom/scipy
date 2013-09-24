!Program made up of compiled functions of 1,2, and 3 variables
!To be compiled by f2py in driver test file
program fortranFns

!print *, 'oneDCompiled(2): (should be 4)', oneDCompiled(2.0)
print *, 'success'

end program


Real*8 function oneDCompiled(x) !Simple 1 d function compiled to fortran
  Real*8 x
!f2py intent(in) x
!f2py intent(out) oneDCompiled
  oneDCompiled = x+2
  return
end function


Real*8 function twoDCompiled(x,y) !Two dimensional integral 
  Real*8 x
  Real*8 y
!f2py intent(in) x 
!f2py intent(in) y
!f2py intent(out) twoDCompiled
  twoDCompiled = x**2+y**2
  return
end function
