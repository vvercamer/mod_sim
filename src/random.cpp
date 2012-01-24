
#include "random.h"

gsl_rng* random_init()
{
	srand(time(NULL));
//	const gsl_rng_type* T;
//	gsl_rng_env_setup();
//	T = gsl_rng_default;
//	return gsl_rng_alloc(T);
	gsl_rng * rand_gen;
	rand_gen = gsl_rng_alloc(gsl_rng_taus);
	gsl_rng_set(rand_gen,time(NULL));
	return rand_gen;
}

double uniform_law()
{
	double x=0.;	

	x = rand()/double(RAND_MAX);

	return x;
}

double arbitrary_law(double (*distribution)(double x), double lower_dist, double upper_dist, double max_distrib)
{
	double u=0;
	double v=0;

	if( (upper_dist-lower_dist) <= 0 ){
		cerr << "-- ERROR -- Attempted to use a wrong distribution in arbitrary_law (min/max)!" << endl;
		exit(EXIT_FAILURE);
	}

	if( max_distrib <= 0 ){
		cerr << "-- ERROR -- Attempted to use a wrong distribution in arbitrary_law (max_distrib) !" << endl;
		exit(EXIT_FAILURE);
	}
	
	do {
		u=uniform_law();
		v=(upper_dist-lower_dist)*uniform_law();
	}while ( u > (*distribution)(v) / max_distrib );
	return v;
}

double parametric_arbitrary_law(double (*distribution)(double x, double p), double parameter, double lower_dist, double upper_dist, double max_distrib)
{
	double u=0;
	double v=0;

	if( (upper_dist-lower_dist) <= 0 ){
		cerr << "-- ERROR -- Attempted to use a wrong distribution in arbitrary_law (min/max)!" << endl;
		exit(EXIT_FAILURE);
	}

	if( max_distrib <= 0 ){
		cerr << "-- ERROR -- Attempted to use a wrong distribution in arbitrary_law (max_distrib) !" << endl;
		exit(EXIT_FAILURE);
	}
	
	do {
		u=uniform_law();
		v=(upper_dist-lower_dist)*uniform_law();
	}while ( u > distribution(v,parameter) / max_distrib );
	return v;
}

double exp_rand(double param)
{
  double random = -1 * 1/param * gsl_sf_log(uniform_law());
  return random;
}

double sign_rand()
{
	double x = uniform_law()-0.5;
	if (x > 0) return 1;
	else return -1;
}

//double gsl_ran_exponential (const gsl rng * r, double mu)