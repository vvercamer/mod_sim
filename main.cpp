#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_math.h>
using namespace std;

//random
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_histogram.h>

#include "random.h"
#include "file_maker.h"
#include "experiment.h"
//#include "gnuplot.h"

int main(int argc, char *argv[])
{
	cout << "Start" << endl;

// ********** BAC A SABLE **********	
	Experiment* experiment = new Experiment(49500); //49,5 keV pour le thorium
	experiment->event();	

// ********** FIN BAC A SABLE **********	

		
	//initialisation random
	gsl_rng *r;
	r = random_init();
	
	// uniform, gaussian, exponential and arbitrary laws
	
	double sigma=1;
	double mu=1;
	int i;
	int n = 20000;
	double *omega0 = new double [n];
	double *omega1 = new double [n];
	double *omega2 = new double [n];
	double *omega3 = new double [n];


	for (i = 0 ; i < n ; i++ )
	{
		omega0[i]=uniform_law();
		omega1[i]=gsl_ran_gaussian(r, sigma);	//p(x)dx = √(2πσ^2) exp(−x^2/(2σ^2))dx
		omega2[i]=gsl_ran_exponential(r, mu); //p(x)dx = 1/µ * exp(−x/μ)dx
		omega3[i]=arbitrary_law();
	}

	//Histogramme


	int ncolumns = 2;
	int nbhist = 100;
	double hmin = -1;
	double hmax = 1.1;
	double *histogram = new double [nbhist];
	double *N = new double [nbhist];
	double *N2 = new double [nbhist];
	double **outtable = new double* [nbhist];
	for( i=0 ; i < nbhist ; i++ )
    	outtable[i] = new double[ncolumns]; //2:nb de colonnes

	size_t nhist = size_t(nbhist);	
	gsl_histogram *h = gsl_histogram_alloc(nhist);
	gsl_histogram_set_ranges_uniform (h, -hmax, hmax);

	for (i = 0 ; i < n ; i++) {
		gsl_histogram_increment (h, omega3[i]);
	}

	for (i = 0 ; i < nbhist ; i++) {
		histogram[i] = gsl_histogram_get (h, i);
		N[i] = (-(double(nbhist) - 1) / 2 + i) * hmax * 2 / nbhist;
		N2[i] = hmin + (hmax - hmin) * (i + 1/2.) / nbhist ;
		outtable[i][0]=N[i];
		outtable[i][1]=histogram[i];
	}
	
	gsl_histogram_free (h);

	//Gnuplot
   	//GNUplot gp;dd
   	//gp.draw(N,histogram,nbhist);
   	

   	
   	int *size = new int [2];
   	size[0] = nbhist; // lignes
   	size[1] = ncolumns; // colonnes 
   	string filename="test.csv";
   	//écriture dans les fichiers (taille, pointeur vers un tableau, nom fichier)
   	file_maker(size, outtable, filename);

   	size[0] = n;
   	size[1] = 1;

	double **outtable2 = new double* [n];
	for( i=0 ; i < n ; i++ )
    	outtable2[i] = new double[2]; //1:nb de colonnes

   	filename = "data";
   	for ( i = 0 ; i < n ; i++) {
	   	outtable2[i][0] = omega3[i];
	   	outtable2[i][1] =0;
   	}
   	
   	file_maker(size, outtable2, filename);   	
   	delete [] size;
	
	// ménage
	gsl_rng_free (r);
	delete [] outtable;
	delete [] outtable2;
	delete [] omega0;
	delete [] omega1;
	delete [] omega2;
	delete [] omega3;
	delete [] N;
	delete [] N2;
	delete [] histogram;
	
	
	
	cout << "The END" << endl;

	return 0;
}

