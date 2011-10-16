#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "random.h"

void random_init (gsl_rng *r)
{
	
    return;
}

double uniform_law ()
{
	float x=0.;	

	x = rand()/float(RAND_MAX);

	return x;
}


//double gaussian_law	




//double exponential_law (int n)
//{
//	
//}
//double gsl_ran_exponential (const gsl rng * r, double mu)