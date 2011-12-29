#include "source.h"

Source::Source(gsl_rng * rng, double energy, double sourceSigma) : rng_(rng), energy_(energy), sourceSigma_(sourceSigma)
{
	sourcePosition_[0]=0;
	sourcePosition_[1]=0;
	sourcePosition_[2]=0;
}

Source::~Source()
{
	
}

Particle* Source::emitParticle()
{
	//fonction qui aura pour but de créer la particule primaire et de retourner, lors de son appel, la valeur du pointeur de l’objet de la classe particule ainsi généré.
	double energy = energy_ + gsl_ran_gaussian(rng_, sourceSigma_);
	Particle* primary = new Particle(rng_,energy,0,0,sourcePosition_);	
	return primary;
}
