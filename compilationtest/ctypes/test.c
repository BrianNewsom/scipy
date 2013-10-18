
#include <stdio.h>

double oneD(double x);
double twoD(double x, double y);


int main(){
  printf("inside main");
  //int q = oneD(6);
  //printf("%i",q);
  return 6;
}

double oneD(double x){
  return x+2.0;
}

double twoD(double x, double y){
  return x*x + y*y;
}
