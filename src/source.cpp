#include "source.h"

Source::Source(gsl_rng * rng, sourceParameters parameters):
rng_(rng), energy_(parameters.energy), sigma_(parameters.sigma)
{
	position_[0]=parameters.position[0];
	position_[1]=parameters.position[1];
}

Source::~Source()
{
	
}

Particle* Source::emitParticle()
{
	//fonction qui aura pour but de créer la particule primaire et de retourner, lors de son appel, la valeur du pointeur de l’objet de la classe particule ainsi généré.
	double energy = energy_ + gsl_ran_gaussian(rng_, sigma_);
	double theta=uniform_law()*2*M_PI;
	Particle* primary = new Particle(rng_,energy,theta,position_);	
	return primary;
}
