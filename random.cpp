
#include "random.h"

gsl_rng* random_init()
{
	srand(time(NULL));
	const gsl_rng_type* T;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	return gsl_rng_alloc(T);
}

double uniform_law()
{
	double x=0.;	

	x = rand()/double(RAND_MAX);

	return x;
}

double arbitrary_law()
{
	double a=0;
	double b=1;
	double M=1;
	double u=0;
	double v=0;
	
	do {
		u=uniform_law();
		v=(b-a)*uniform_law();
	}while ( u > arbitrary_function(v) / M );
	return v;
}

double arbitrary_function(double x)
{
	return x*x;
}


//double gaussian_law	




//double exponential_law (int n)
//{
//	
//}
//double gsl_ran_exponential (const gsl rng * r, double mu)