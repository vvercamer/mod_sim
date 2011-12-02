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
	cout << "\n****************************************" << endl
		   << "********  START THE SIMULATION  ********" << endl
		   << "****************************************\n" << endl;
	
	int nEvents = 100;
	if (argc == 2)
		nEvents = atoi(argv[1]);

	cout << "-- INFO -- New experiment" << endl;		
	Experiment* experiment = new Experiment(49500); //49,5 keV pour le thorium

	cout << "-- INFO -- New event" << endl;	
	experiment->event();
	
	cout << "-- INFO -- The END" << endl;

	return 0;
}

