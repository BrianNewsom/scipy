#include <stdio.h>
#include "quadpack.h"
//extern void qag_(float(*)(float *), float *, float *, float *, float *, int *,
	//	 float*, float*, int*, int*, int*, int*, int*, int(*) [50], float(*) [200]);
//extern float integrand_(float *);
extern "C"{
  float integral_(float*, float*);
}

float integrand(float *x){
  return (*x) * (*x) + 4. * *x - 12.;
}


int main()
{
  float a, b, epsabs, epsrel, result, abserr;
  int key, neval, ier, last;
  int limit = 50;
  int lenw = 200;
  int iwork[50];
  float work[200];
  
  a = -1.;
  b = 1.;
  epsabs = 1e-3;
  epsrel = 1e-3;
  key = 1;
  qag_(&integrand,&a,&b,&epsabs,&epsrel,&key,
       &result,&abserr,&neval,&ier,&limit,&lenw,&last,&iwork,&work);
  printf("%f\n",result);
  printf("%f\n",integral_(&a,&b));
}


