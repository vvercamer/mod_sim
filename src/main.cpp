#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_math.h>
#include <sys/time.h>
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

#define ERROR 0
#define WARNING 1
#define INFO 2
#define DEBUG 3

int LogLevel = INFO;

int main(int argc, char *argv[])
{
	struct timeval startTime;
    struct timeval endTime;
	
	gettimeofday(&startTime, NULL);
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

	double* scintillationEnergy = new double [nEvents];

	collimatorParameters cParam;
	detectorParameters dParam;
	sourceParameters sParam;

// en cm

	cParam.position[0]=-1.5;
	cParam.position[1]=0;
	cParam.diameter=2.5;

	dParam.position[0]=3;
	dParam.position[1]=0;
	dParam.diameter=7.6;
	dParam.width=7.6;
	
	sParam.position[0]=0;
	sParam.position[1]=0;
	sParam.energy=sourceEnergy;
	sParam.sourceType=0;

	if(LogLevel>1) cerr << "-- INFO -- New experiment" << endl;		
	Experiment* experiment = new Experiment(sParam, cParam, dParam); //energie 49,5 keV pour le thorium

	if(LogLevel>1) cerr << "-- INFO -- Starting for " << nEvents << " events" << endl;		
	for (i=0; i<nEvents; i++){
		scintillationEnergy[i]= experiment->event(sParam.sourceType);
	}
	


	if(LogLevel>1) cerr << "-- INFO -- Making the output files" << endl;

	if (sParam.sourceType == 22)
		sourceEnergy = 1675;

	if (sParam.sourceType == 60)
		sourceEnergy = 2350;

	histo_maker(nEvents,scintillationEnergy,sourceEnergy*1.1);
	
	delete[] scintillationEnergy;
	delete experiment;
	
	if(LogLevel>1) cerr << "-- INFO -- The END" << endl;
	
    gettimeofday(&endTime, NULL);
    double tS = startTime.tv_sec*1000000 + (startTime.tv_usec);
    double tE = endTime.tv_sec*1000000  + (endTime.tv_usec);
    cout << "-- INFO -- execution time : " << (tE - tS)*1e-6 << " s" << endl;

	return 0;
}

