#ifndef _EXPERIMENT_H_INCLUDED
#define _EXPERIMENT_H_INCLUDED
#include "particle.h"
#include "source.h"

class Experiment {
private :
	Source *source;
	Particle *stack;
	
public :
	Experiment();
	~Experiment();
	void StartOfRun(int, char **);
	void EndOfRun();
	void Event();

};

#endif