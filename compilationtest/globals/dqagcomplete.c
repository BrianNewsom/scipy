#include <stdio.h>
#include <stdlib.h>

double* globalargs; //Array to store global parameters (x1,...,xn)
double (*globalf)(double *); //Void pointer that will hold function to be later typed
int globalnargs; //Int to store number of elements in globargs.  (Only used if we use quad_function rather than alt)

double g1base(double args[2]){ //User presents variables as an array
	return args[0]*4 + 7 + args[1];
}

void init(double (*f)(double *), double args[], int nargs){
	//Initialize everything necessary
	globalf = f;
	globalnargs = nargs;
	globalargs = args;

}


double call(double* x){ // Gets rid of need for switch statement. User must define function as in g1 or g2
	double (*foo)(double* args) = globalf;
	double* args = globalargs;
	args[0] = *x;
	return foo(args);
}

double dqag2(double (*f)(double *), double* args, int nargs, double a, double b, double epsabs,
		double epsrel,int key, int limit, int lenw, int last, int iwork[50],double work[200]){ //Evaluate Dqags
	double result, abserr; //Return params that don't need to be passed in.
	int neval, ier; //Return params that don't need to be passed in.

  	init(f,args,nargs); //Sets params globally for call function

	dqag_(call,&a,&b,&epsabs,&epsrel,&key,&result,&abserr,&neval,&ier,&limit,&lenw,&last,&iwork,&work);
	printf("\n");
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
  	//Of course these don't need to be declared, they are just done for simplicity.
	int nargs = 2;
	double args[nargs]; //These 3 do need to be declared. Should this be here? How will this be done?
	args[1] = 0;
	dqag2(g1base, args,nargs,a,b,epsabs,epsrel,key,limit,lenw,last,iwork,work);
	//dqag2(g2base, )
	return 0;
}



