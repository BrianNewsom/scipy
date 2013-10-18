#include <stdio.h>
//#include "quadpack.h"
#include "quadpack.h"
#include <iostream>
//extern void qag_(float(*)(float *), float *, float *, float *, float *, int *,
	//	 float*, float*, int*, int*, int*, int*, int*, int(*) [50], float(*) [200]);
//extern float integrand_(float *);
// extern "C" {
//   float integral_(float*, float*);
// }

float integrand(float* x){ //FUNCTION TO BE INTEGRATED WILL PROBABLY BE EXTERNAL
  return (*x) * (*x) + 4. * *x - 12.;
}

float fnArray(float xes[], int nx, float ts[], int nt);

int main()
{
  function* test = new function(&integrand);// = new function class from passed integrand;
  std::cout << "constructed" << std::endl;
  test->eval(); //eval function
  std::cout << "eval'd";
  test->integrate(); //integrate function
  std::cout << "integrated" << std::endl;
}

float fnArray(float xes[], int nx, float ts[], int nt){
  return xes[0]+xes[1]*xes[1] + ts[0];
}
