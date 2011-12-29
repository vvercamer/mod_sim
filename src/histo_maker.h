#ifndef _HISTO_H_INCLUDED
#define _HISTO_H_INCLUDED


#include <iostream>
//#include <math.h>
//#include <gsl/gsl_math.h>
using namespace std;

#include <gsl/gsl_histogram.h>

#include "file_maker.h"

void histo_maker(int n, double* omega, double hmax);

#endif