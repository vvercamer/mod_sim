#ifndef _EXPERIMENT_H_INCLUDED
#define _EXPERIMENT_H_INCLUDED
#include "particle.h"
#include "source.h"
#include <iostream>
using namespace std;


class Experiment {
private :
	Source *source_;
	Particle *topOfStack_;
	//plus tard : initialiser l'enceinte, le collimateur et le détecteur.
	
public :
	Experiment(double energy);
	~Experiment();
//	void StartOfRun(int, char **);
//	void EndOfRun();
	void event();
	Particle* getTopOfStack();
	void setTopOfStack(Particle*);
	void showStack();
	void add2Stack(Particle *);
	void removeFromStack(Particle *);
};

#endif