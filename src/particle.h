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

double compton_distrib(double x, double ksi);

class Particle {
private : // définition les données membres de la classe
	static int n_particles_;
	gsl_rng * rng_;
	double energy_, theta_, phi_;
	double position_[3];
	Particle *next_;
	
	//private functions
	int selectInteractionType(double *** data);
	void PhotoElectric(int atom, interactionResult* result);
	void Compton(interactionResult* result);
	void PairProduction(interactionResult* result);
	
public : // définition les fonctions membres de la classe
//	Particle(gsl_rng * rng, double energy);
	Particle(gsl_rng * rng, double energy, double theta, double phi, double position[3]);
	~Particle();
//	void setPosition(){};
	Particle* getNext();	void setNext(Particle* next);
	void countParticles();
	double Propagation(double lambda);
	interactionResult Interaction(double *** data);
	double getEnergy(){return energy_;};
	
};

#endif
