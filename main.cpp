#include <iostream>
#include <math.h>
#include <gsl/gsl_math.h>
using namespace std;

//random
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_histogram.h>


#include "random.h"
#include "gnuplot.h"

int main(int argc, char *argv[])
{

	//initialisation random
	gsl_rng *r;
	srand(time(NULL));
    const gsl_rng_type *T;
	gsl_rng_env_setup();
	gsl_rng_default_seed = rand();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
//	random_init(r);
	cout << "ok" << endl;

	//gaussian
	
	double sigma=0.5;
	int i;
	int n = 20000;
	double *omega = new double [n];

	for (i = 0 ; i < n ; i++ )
		omega[i]=gsl_ran_gaussian(r, sigma);

	
	// uniform	
	float x = 0;
	x=uniform_law();
	cout << x << endl;


	//Histogramme

	size_t nhist = 100;
	int nbhist = (int) nhist;
	double hmax = 3;
	double *hist1 = new double [nbhist];
	double *N = new double [nbhist];
	
	gsl_histogram *h = gsl_histogram_alloc(nhist);
	gsl_histogram_set_ranges_uniform (h, -hmax, hmax);

	for (i = 0 ; i < n ; i++) {
		gsl_histogram_increment (h, omega[i]);
	}

	for (i = 0 ; i < nbhist ; i++) {
	hist1[i] = gsl_histogram_get (h, i);
	N[i]=i;
	}
	
	gsl_histogram_free (h);

	//Gnuplot
   	GNUplot gp;
   	gp.draw(N,hist1,nhist);
	
	// ménage
	gsl_rng_free (r);
	delete omega;
	delete N;
	delete hist1;

	return 0;
}


