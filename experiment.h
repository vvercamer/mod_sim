#ifndef _EXPERIMENT_H_INCLUDED
#define _EXPERIMENT_H_INCLUDED
#include "particle.h"
#include "source.h"
#include "detector.h"
#include "random.h"
#include "interaction_data.h"

#include <iostream>
using namespace std;


class Experiment {
private :
	Source *source_;
	Detector *detector_;
	Particle *topOfStack_;
	gsl_rng *rng_;
	double *** data;
	//plus tard : initialiser l'enceinte, le collimateur et le détecteur.
	
public :
	Experiment(double energy, int nDynodes);
	~Experiment();
//	void StartOfRun(int, char **);
//	void EndOfRun();
	void event();
	Particle* getTopOfStack();
	void setTopOfStack(Particle*);
	void showStack();
	void add2Stack(Particle *);
	void removeTopOfStack();
};

#endif