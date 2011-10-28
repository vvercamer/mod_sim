#ifndef _EXPERIMENT_H_INCLUDED
#define _EXPERIMENT_H_INCLUDED
#include "particle.h"
#include "source.h"

class Experiment {
private :
	Source *source_;
	Particle *stack_;
	//plus tard : initialiser l'enceinte, le collimateur et le détecteur.
	
public :
	Experiment();
	~Experiment();
	void StartOfRun(int, char **);
	void EndOfRun();
	void Event();
	Particle* getStack();

};

#endif