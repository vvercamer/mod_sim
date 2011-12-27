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
	cerr << "\n****************************************" << endl
		   << "********  START THE SIMULATION  ********" << endl
		   << "****************************************\n" << endl;

	int i;	

	int nEvents = 1;
	double sourceEnergy = 49.5; //en keV
	if (argc == 3) {
		nEvents = atoi(argv[1]);
		sourceEnergy = atof(argv[2]); //en keV
	}
	else if (argc != 3 && argc != 1) {
		cerr << "-- ERROR -- Proper use is ./simulation OR ./simulation <nEvents> <sourceEnergy (keV)> " << endl;
		exit(EXIT_FAILURE);
	}

	cerr << "-- INFO -- New experiment" << endl;		
	Experiment* experiment = new Experiment(sourceEnergy); //energie 49,5 keV pour le thorium

	for (i=0; i<nEvents; i++){
		experiment->event();
	}
	
	cerr << "-- INFO -- The END" << endl;

	return 0;
}

