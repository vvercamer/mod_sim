#ifndef _SOURCE_H_INCLUDED
#define _SOURCE_H_INCLUDED
#include "particle.h"

#include <iostream>
using namespace std;

class Source {
private :
	gsl_rng* rng_;
	double energy_;
	double sourceSigma_;
	double sourcePosition_[3];
	
public :
	Source(gsl_rng*, double energy, double sourceSigma);
	~Source();
//	double getEnergy(void){return(energy);};
//	void setEnergy(double a){energy=a;};
	Particle* emitParticle();
};

#endif