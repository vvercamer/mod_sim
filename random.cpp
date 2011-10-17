
#include "random.h"

gsl_rng* random_init()
{
	const gsl_rng_type* T;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	return gsl_rng_alloc(T);
}

double uniform_law ()
{
	double x=0.;	

	x = rand()/double(RAND_MAX);

	return x;
}

double arbitrary_law ()
{
	double x=0.;
	return x;
}


//double gaussian_law	




//double exponential_law (int n)
//{
//	
//}
//double gsl_ran_exponential (const gsl rng * r, double mu)