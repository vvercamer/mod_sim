#ifndef _SOURCE_H_INCLUDED
#define _SOURCE_H_INCLUDED
#include "particle.h"

#include <iostream>
using namespace std;

class Source {
private :
//	double energy;
	
public :
	Source();
	~Source();
//	double getEnergy(void){return(energy);};
//	void setEnergy(double a){energy=a;};
	Particle* emitParticle();
};

#endif