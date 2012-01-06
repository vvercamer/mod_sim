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
#include "histo_maker.h"
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
	double sourceSigma = 2;
	if (argc == 3) {
		nEvents = atoi(argv[1]);
		sourceEnergy = atof(argv[2]); //en keV
	}
	else if (argc != 3 && argc != 1) {
		cerr << "-- ERROR -- Proper use is ./simulation OR ./simulation <nEvents> <sourceEnergy (keV)> " << endl;
		exit(EXIT_FAILURE);
	}

	double *scintillationEnergy = new double [nEvents];

	collimatorParameters cParam;
	detectorParameters dParam;
	sourceParameters sParam;

	cParam.position[0]=-1;
	cParam.position[1]=0;

	dParam.position[0]=0;
	dParam.position[1]=0;
	dParam.diameter=0.02;
	
	sParam.position[0]=0;
	sParam.position[1]=0;
	sParam.diameter=0.05;
	sParam.width=0.05;
	sParam.energy=sourceEnergy;
	sParam.sigma=sourceSigma;

	cerr << "-- INFO -- New experiment" << endl;		
	Experiment* experiment = new Experiment(sParam, cParam, dParam); //energie 49,5 keV pour le thorium

	for (i=0; i<nEvents; i++){
		scintillationEnergy[i]=experiment->event();
	}
	
	histo_maker(nEvents,scintillationEnergy,sourceEnergy*1.1);
	
	cerr << "-- INFO -- The END" << endl;

	return 0;
}

