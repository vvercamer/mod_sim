#ifndef _EXPERIMENT_H_INCLUDED
#define _EXPERIMENT_H_INCLUDED
#include "particle.h"
#include "source.h"
#include "collimator.h"
#include "detector.h"
#include "random.h"
#include "interaction_data.h"

#include <iostream>
using namespace std;

extern int LogLevel;

class Experiment {
private :
	Source *source_;
	Collimator *collimator_;
	Detector *detector_;
	Particle *topOfStack_;
	gsl_rng *rng_;
	double *** data;
	// functions
	Particle* getTopOfStack();
	void showStack();
	void add2stack(Particle* particle);
	void removeTopOfStack();
	//plus tard : initialiser l'enceinte, le collimateur et le détecteur.
	
public :
	Experiment(sourceParameters sParam, collimatorParameters cParam, detectorParameters dParam);
	~Experiment();
//	void StartOfRun(int, char **);
//	void EndOfRun();
	double event(int sourceType);
};

#endif