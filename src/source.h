#ifndef _SOURCE_H_INCLUDED
#define _SOURCE_H_INCLUDED
#include "particle.h"
#include "random.h"

#include <iostream>
using namespace std;

extern int LogLevel;

typedef struct
{
	double position [2];
	double energy;
	int sourceType;
} sourceParameters;

typedef struct {
	int nParticlesEmitted;
	Particle ** particlesEmitted;
} sourceEmission;

class Source {
private :
	gsl_rng* rng_;
	double energy_;
	double position_[2];
	int sourceType_;
	
public :
	Source(gsl_rng * rng, sourceParameters parameters);
	~Source();
	sourceEmission emitParticle(int sourceType);
};

#endif