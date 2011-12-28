#ifndef _RANDOM_H_INCLUDED
#define _RANDOM_H_INCLUDED

#include <iostream>
using namespace std;
#include <gsl/gsl_rng.h>
#include <math.h>
//#include <gsl/gsl_randist.h>

extern gsl_rng* random_init(void);

double uniform_law(void);

double arbitrary_law(double (*distribution)(double x), double lower_dist, double upper_dist, double max_distrib);

double parametric_arbitrary_law(double (*distribution)(double x, double p), double p, double lower_dist, double upper_dist, double max_distrib);

#endif
