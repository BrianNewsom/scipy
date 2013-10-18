#include <cstdlib>
#include <iostream>
#include "g2c.h"
#include <gfortran.h>


using namespace std;

int main(){
	doublereal integrand(doublereal x);
	extern void dqags_(doublereal*(*doublereal), *doublereal, *doublereal, *doublereal epsabs, doublereal epsrel, doublereal result, doublereal abserr, integer neval, integer ier, integer limit, integer lenw, integer last, integer iwork[], integer work[]); 
	//NOT SURE OF RETURN TYPE (INTEGRAND,A,B,EPSABS,EPSREL,RESULT, ABSERR, NEVAL, IER, LIMIT, LENW, LAST, IWORK, WORK)
	const integer LIMIT = 50; //Define PARAMS here
	const integer LENW = 200; //Use this or #define
	doublereal a, b, epsabs, epsrel, result, abserr; //doubleprecision
    integer neval, ier, last; //integer
    integer iwork(LIMIT); //Check this array
    doublereal work(LENW);
    //extern doublereal DQAGS, INTEGRAND, INTEGRAL; //doubles?
    a = -1.;
    b = 1.;
    epsabs = 1E-3;
    epsrel = 1E-3;
    cout << integrand(a) << endl; //This fn works


    dqags_(integrand, a,b,epsabs,epsrel,result,abserr,neval,ier,LIMIT,LENW,last,iwork,work);
    	//(INTEGRAND,A,B,EPSABS,EPSREL,RESULT, ABSERR, NEVAL, IER, LIMIT, LENW, LAST, IWORK, WORK);
    cout << "hello world" << endl;



  return 0;
}


    //  FUNCTION INTEGRAND (X)
    //IMPLICIT NONE
    //DOUBLE PRECISION X
    //  /DOUBLE PRECISION INTEGRAND
    //  INTEGRAND = X**2 + 4.*X - 12.
    //  END FUNCTION INTEGRAND

doublereal integrand(doublereal x){
	doublereal integrand;
	integrand = x*x+4*x -12;
	return integrand;
}