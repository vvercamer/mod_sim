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
	double sourceEnergy = 662; //en keV
	int sourceType = 0;

	cerr << LogLevel<<endl;

	if (argc == 5) {
		nEvents = atoi(argv[1]);
		sourceEnergy = atof(argv[2]); 	//en keV
		sourceType = atoi(argv[3]); 	// 0 22 ou 60
		LogLevel = atoi(argv[4]); 		// 0 1 2 ou 3
	}
	
	else if (argc != 5 && argc != 1) {
		cerr << "-- ERROR -- Proper use is ./simulation OR ./simulation <nEvents> <sourceEnergy (keV)> <sourceType> <LogLevel> " << endl;
		exit(EXIT_FAILURE);
	}

	if (LogLevel != 0 && LogLevel != 1 && LogLevel != 2 && LogLevel != 3) {
		cerr << "-- ERROR -- LogLevel must be 0(ERROR), 1(WARNING) 2(INFO) or 3(DEBUG) !" << endl;
		exit(EXIT_FAILURE);
	}

	double* scintillationEnergy = new double [nEvents];

	collimatorParameters cParam;
	detectorParameters dParam;
	sourceParameters sParam;

	// if you want to ignore the collimator set a negative value for cParam.position[0]
	cParam.position[0]=-1;		// en cm
	cParam.position[1]=0;		// en cm
	cParam.diameter=2.5;		// en cm


	dParam.position[0]=4;		// en cm
	dParam.position[1]=0;		// en cm
	dParam.diameter=7.6;		// en cm
	dParam.width=7.6;			// en cm
	
	sParam.position[0]=0;		// en cm
	sParam.position[1]=0;		// en cm
	sParam.energy=sourceEnergy;
	sParam.sourceType=sourceType;

	if(LogLevel>1) cerr << "-- INFO -- New experiment" << endl;		
	Experiment* experiment = new Experiment(sParam, cParam, dParam);
	
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

