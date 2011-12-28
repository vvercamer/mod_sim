#ifndef _PARTICLE_H_INCLUDED
#define _PARTICLE_H_INCLUDED

//#include <vector> //http://www.fredosaurus.com/notes-cpp/stl-containers/vector/header-vector.html
#include <iostream>
using namespace std;

#include "random.h"
#include "interaction_data.h"

#include <gsl/gsl_sf_log.h>			// ln
#include <gsl/gsl_randist.h> // loi exp


typedef struct
{
	int nParticlesCreated;
	void ** particlesCreated;
	double depositedEnergy;
} interactionResult;



class Particle {
private : // définition les données membres de la classe
	static int n_particles_;
	gsl_rng * rng_;
	double theta_, phi_, energy_;
	double position_[3];
	Particle *next_;
	
public : // définition les fonctions membres de la classe
	Particle(gsl_rng *, double);
	~Particle();
//	void setPosition(){};
	Particle* getNext();	void setNext(Particle*);
	int selectInteractionType(double ***);
	void countParticles();
	double Parcours();
	double Propagation(double);
	interactionResult Interaction(double ***);
	double getEnergy(){return energy_;};
};

#endif
