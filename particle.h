#ifndef _PARTICLE_H_INCLUDED
#define _PARTICLE_H_INCLUDED

//#include <vector> //http://www.fredosaurus.com/notes-cpp/stl-containers/vector/header-vector.html
#include <iostream>
using namespace std;

#include "probabilities.h"
#include "random.h"
#include <gsl/gsl_sf_log.h>			// ln
#include <gsl/gsl_randist.h> // loi exp

// définition des types
#define PHOTON 0
#define ELECTRON 1
#define POSITRON 2
#define IODINE 3
#define SODIUM 4

class Particle {
private : // définition les données membres de la classe
	static int n_particles_;
	gsl_rng * rng_;
	int type_;
	double theta_, phi_, energy_;
	double position_[3];
	Particle *next_;
	
public : // définition les fonctions membres de la classe
	Particle(gsl_rng *, int, Particle *);
	~Particle();
	int getType();
	void setType(int);
//	void setPosition(){};
	Particle* getNext();	void setNext(Particle*);
	int chooseInteractionType();
	void countParticles();
	double Parcours();
	double Propagation(double);
	void Interaction();
};

#endif
