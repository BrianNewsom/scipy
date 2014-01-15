#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static const double  PI=3.14159265359;

double* globalargs; //Array to store function parameters (x1,...,xn)
double (*globalf)(int, double *); //Pointer to function of array
int globalnargs; //Int to store number of elements in globargs.  I'm not totally sure this is necessary.

double dqagF(int n, double args[n]){ //User presents variables as an array
  //return *x0*4 + 7 + args[1];
  return 4*args[0] + args[1] + 7;
}

double dqagpF(int n, double args[n]){
  return 7/((1-args[0])*(2-args[0])) + 7*args[1];
}

double dqngF(int n, double args[n]){
  return args[0]*args[0] + args[1];
}

double dqawoF(int n, double args[n]){
  return log(args[0]) * sin(10*PI*args[0]) + args[1];
}
void init(double (*f)(int, double *), int n, double args[n]){
  //Initialize 
  globalnargs = n;
  globalf = f;
  globalargs = args;

}

double call(double* x){ // Evaluates user defined function as function of one variable.
  //We want to create a new array with [x0, concatenated with [x1, . . . , xn]]
  double (*f)(int, double *) = globalf;
  double evalArray[globalnargs];
  int i = 1;
  evalArray[0] = *x;
  
  for(i; i < globalnargs ; i++)
    evalArray[i] = globalargs[i]; //Add everything from globalargs to end of evalArray
  
  return f(globalnargs, evalArray);
}

double dqag2(double (*f)(int, double *), int nargs, double args[nargs], double a, double b,
       double epsabs, double epsrel,int key, double result, double abserr, int neval, int ier,
       int limit, int lenw, int last, int iwork[limit], double work[lenw]){//User called function

  init(f,nargs,args); //Sets params globally for call function

  dqag_(call,&a,&b,&epsabs,&epsrel,&key,&result,&abserr,&neval,&ier,&limit,&lenw,&last,&iwork,&work);
  printf("%f\n",result);
}

double dqng2(double (*f)(int, double *), int nargs, double args[nargs], double a, double b, 
        double epsabs, double epsrel, double result, double abserr, int neval, int ier){
  init(f,nargs,args);

  dqng_(call,&a,&b,&epsabs,&epsrel,&result,&abserr,&neval,&ier);
  printf("%f\n",result);

}

double dqawo2(double (*f)(int, double *), int nargs, double args[nargs], double a, double b,
        double omega, int integr, double epsabs, double epsrel, double result, double abserr,
        int neval, int ier, int leniw, int maxp1, int lenw, int last, int iwork[leniw],
        double work[lenw]){
  init(f,nargs,args);

  dqawo_(call, &a, &b, &omega, &integr, &epsabs, &epsrel, &result, &abserr, &neval, &ier, 
        &leniw, &maxp1, &lenw, &last, &iwork, &work);
  printf("%f\n",result);

}


double dqagp2(double (*f)(int, double *), int nargs, double args[nargs], double a, double b, 
       int npts2, double points[npts2], double epsabs, double epsrel, double result,
       double abserr, int neval, int ier, int leniw, int last,int lenw, 
       int iwork[leniw], double work[lenw]){

  init(f,nargs,args);

  dqagp_(call,&a,&b,&npts2,&points,&epsabs,&epsrel,&result,&abserr,&neval,&ier,&leniw,&lenw,&last,&iwork,&work);
     //    SUBROUTINE DQAGP (F, A, B, NPTS2, POINTS, EPSABS, EPSREL, RESULT,
     // +   ABSERR, NEVAL, IER, LENIW, LENW, LAST, IWORK, WORK)
  printf("%f\n",result);
}
       


int main(){
  double epsabs, epsrel;
  int key, last;
  int limit = 50;
  int lenw = 200;
  int iwork[50];
  double work[200];
  double a = -1.;
  double b = 1.;
  epsabs = 1e-3;
  epsrel = 1e-3;
  key = 1;
  double result, abserr;
  int neval, ier;
  //Of course these don't need to be declared, this is just done for simplicity.
  int nargs = 2;
  double args[nargs]; //These 3 do need to be declared. Should this be here? How will this be done?
  args[1] = 12;
  dqag2(dqagF,nargs,args,a,b,epsabs,epsrel,key,result,abserr,neval,ier,limit,lenw,last,iwork,work);
  ////////////////////////////////////
  dqng2(dqngF,nargs,args,a,b,epsabs,epsrel,result,abserr,neval,ier);
  ////////////////////////////////////
  double omega = 10 * PI;
  int integr = 2;
  int maxp1 = 2;
  int leniw = 50;
  dqawo2(dqawoF, nargs, args, a,b, omega, integr, epsabs, epsrel, result, abserr,
        neval, ier, leniw, maxp1, lenw, last, iwork, work);
  ////////////////////////////////////
  double result2, abserr2;
  int neval2, ier2;
  int last2;

  int nargs2 = 2;
  double args2[nargs2];
  a = -10.;
  b = 10.;
  args2[1] = 12;
  int npts = 2; //Only one singularity
  int npts2 = npts+2; //Multiplied by two

  double points[npts2]; //Length of array is npts2.
  points[0] = 1;
  points[1] = 2;

  //int leniw = 50;
  dqagp2(dqagpF,nargs2, args2, a,b,npts2,points,epsabs,epsrel,result2,abserr2,neval2,ier2,leniw,last2,lenw,iwork,work);
  // double dqagp2(double (*f)(int, double *), int nargs, double args[nargs], double a, double b, 
  //      int npts2, double points[npts2], double epsabs, double epsrel, double result,
  //      double abserr, int neval, int ier, int leniw, int last,int lenw, 
  //      int iwork[leniw], double work[lenw]){

  //call qagp ( f04, a, b, npts2, points, epsabs, epsrel, result, abserr, neval, ier )
    // SUBROUTINE DQAGP (F, A, B, NPTS2, POINTS, EPSABS, EPSREL, RESULT,
    //  +   ABSERR, NEVAL, IER, LENIW, LENW, LAST, IWORK, WORK)
  return 0;
}



