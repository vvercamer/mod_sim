#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <gsl/gsl_rng.h>
#include <math.h>
//#include <gsl/gsl_randist.h>

extern gsl_rng* random_init(void);

double uniform_law(void);

double arbitrary_law();

double arbitrary_function(double x);

#endif