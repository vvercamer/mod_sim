#ifndef _SOURCE_H_INCLUDED
#define _SOURCE_H_INCLUDED
#include "particle.h"
#include "random.h"

#include <iostream>
using namespace std;

typedef struct
{
	double position [2];
	double energy;
	double sigma;
} sourceParameters;

class Source {
private :
	gsl_rng* rng_;
	double energy_;
	double sigma_;
	double position_[2];
	
public :
	Source(gsl_rng * rng, sourceParameters parameters);
	~Source();
	Particle* emitParticle();
};

#endif