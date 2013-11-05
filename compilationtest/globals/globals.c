#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


double* globargs;
void* globf;
int globnargs;
//double (*globf)(double * );

void init(void* func, double args[], int nargs){
	//Initialize everything necessary
	globf = func;
	globnargs = nargs;
	globargs = args;

}

double f1base(double *x0){ //ex function to test w/
	return *x0+2;
}

double f2base(double *x0, double *x1){
	return *x0 + 4 + *x1; //Is this safe? Will x2 always be 0 when called as below?
}

double f3base(double *x0, double *x1){
	return *x0 + 6 + *x1;
}

double f4base(double *x0, double *x1, double *x2){
	return *x0 + 6 + *x1 + 3 * *x2;

}

double f6base(double *x0, double *x1, double *x2, double *x3, double *x4, double *x5){
	return *x0 + 6 + *x1 * *x2 * *x3 * *x4 * *x5;
}

double g1base(double args[1]){ //Alternate declaration style
	return args[0]*4;

}

double g2base(double args[2]){ //Alt
	return args[0]*4 + 7 + args[1];
}

double g3base(double args[3]){
	return 7*args[0] * args[1] * args[2];

}
double quad_functionNOARGS(double* x){ //quad_function analogue (Makes it callable as with only *x)
	//This must set up all the args globally as well 

	double (*foo)(double * ) = globf; // This has to take args, etc.

	return foo(x);

}

double quad_function(double* x){ //quad_function analogue (Makes it callable as with only *x)
	//This must set up all the args globally as well 
	switch (globnargs)
	{
		case 1: 
		{
			double (*foo1) (double * ) = globf;
			return foo1(x);
		}
		case 2: 
		{
			double (*foo2) (double *, double * ) = globf;
			//double (*foo2) = globf;
			return foo2(x, &globargs[1]);
		}
		case 3:
		{
			double (*foo3) (double *, double *, double *) = globf;
			return foo3(x, &globargs[1], &globargs[2]);
		}
		case 4:
		{
			double (*foo4) (double *, double *, double *, double *) = globf;
			return foo4(x, &globargs[1], &globargs[2], &globargs[3]);
		}
		case 5:
		{
			double (*foo5) (double *, double *, double *, double *, double *) = globf;
			return foo5(x, &globargs[1], &globargs[2], &globargs[3], &globargs[4]);
		}
		case 6:
		{
			double (*foo6) (double *, double *, double *, double *, double *, double *) = globf;
			return foo6(x, &globargs[1], &globargs[2], &globargs[3], &globargs[4], &globargs[5]);
		}
		case 7:
		{
			double (*foo7) (double *, double *, double *, double *, double *, double *, double *) = globf;
			return foo7(x, &globargs[1], &globargs[2], &globargs[3], &globargs[4], &globargs[5], &globargs[6]);
		}
		case 8:
		{
			double (*foo8) (double *, double *, double *, double *, double *, double *, double *, double *) = globf;
			return foo8(x, &globargs[1], &globargs[2], &globargs[3], &globargs[4], &globargs[5], &globargs[6], &globargs[7]);
		}
		
		default:
			return -999999;
	}
}

double quad_function_alt(double *x){ // Gets rid of need for switch statement. User must define function as in g1 or g2
	double (*foo)(double* args) = globf;
	double* args = globargs;
	args[0] = *x;
	return foo(args);
}

// //WRITE QUAD_FUNCTION_VARIADIC
// double quad_function_variadic(double *x){
// 	double (*varfunc)(double* x , ...) = globf;
// 	// va_list ap;
// 	// va_start(ap, x);
// 	return 0;
// }

double dqag(double a, double b){ //Evaluate Dqags
	//Currently don't allow choosing integration bounds or anything of the like
	double epsabs, epsrel, result, abserr;
  	int key, neval, ier, last;
  	int limit = 50;
  	int lenw = 200;
  	int iwork[50];
  	double work[200];
  
  	// a = -1.;
  	// b = 1.;
  	epsabs = 1e-3;
  	epsrel = 1e-3;
  	key = 1;

	dqag_(quad_function,&a,&b,&epsabs,&epsrel,&key,&result,&abserr,&neval,&ier,&limit,&lenw,&last,&iwork,&work);
	printf("\n");
	printf("%f\n",result);
}

double dqagalt(double a, double b){ //Evaluate Dqags
	//Currently don't allow choosing integration bounds or anything of the like
	double epsabs, epsrel, result, abserr;
  	int key, neval, ier, last;
  	int limit = 50;
  	int lenw = 200;
  	int iwork[50];
  	double work[200];
  
  	// a = -1.;
  	// b = 1.;
  	epsabs = 1e-3;
  	epsrel = 1e-3;
  	key = 1;

	dqag_(quad_function_alt,&a,&b,&epsabs,&epsrel,&key,&result,&abserr,&neval,&ier,&limit,&lenw,&last,&iwork,&work);
	printf("\n");
	printf("%f\n",result);
}

void test1(){ //Simple test of switch method. Holding all args to 0.
	printf("First method integrating f6 from -1 to 1");
	void* f6 = f6base;
	int nargs = 6; //Number of arguments 1->n
	double expectedresult = 12;//Integrated symbollically in Mathematica
	double args[nargs];
	args[1] = 0; //Const values we want to hold x1 .... xn to
	args[2] = 0; 
	args[3] = 0;
	args[4] = 0;
	args[5] = 0;
	init(f6, args, nargs);
	dqag(-1,1);
	printf("Expected result: ");
	printf("%f\n",expectedresult);

}

void test2(){ //Simple test of array function input. Holding other args to 0.
	printf("Alternate method integrating g2 from -1 to 100");
	void* g2 = g2base;
	int nargs2 = 2;
	double expectedresult = 20705;//Integrated symbollically in Mathematica
	double args2[nargs2];
	args2[1] = 0;
	init(g2,args2,nargs2);

	dqagalt(-1,100);
	printf("Expected result: ");
	printf("%f\n",expectedresult);

}

void test3(){//Now test functionality of args passing (required for multidimension integration) 
	//	return *x0 + 6 + *x1 + 3 * *x2;
	printf("First method integrating f4 from -1000 to .00005, holding args[1] to 7 and args[2] to 8");
	void* f4 = f4base;
	int nargs = 3; //Number of arguments 1->n
	double expectedresult = -463000;//Integrated symbollically in Mathematica
	double args[nargs];
	args[1] = 7; //Const values we want to hold x1 .... xn to
	args[2] = 8; 
	init(f4, args, nargs);
	dqag(-1000,0.00005);
	printf("Expected result: ~");
	printf("%f\n",expectedresult);
}

void test4(){//Now test functionality of args passing (required for multidimension integration) 
	//return 7*args[0] * args[1] * args[2];
	printf("Alternate method integrating g3 from 0 to 19, holding args[1] to 2 and args[2] to 1");
	void* g3 = g3base;
	int nargs = 3; //Number of arguments 1->n
	double expectedresult = 2527;//Integrated symbollically in Mathematica
	double args[nargs];
	args[1] = 2; //Const values we want to hold x1 .... xn to
	args[2] = 1; 
	init(g3, args, nargs);
	dqagalt(0,19);
	printf("Expected result: ");
	printf("%f\n",expectedresult);
}


int main(){
	test1();
	test2();
	test3();
	test4();
	return 0;
}



