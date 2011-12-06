#include "particle.h"

Particle::Particle(gsl_rng * rng, int type, Particle * next): rng_(rng), type_(type), next_(next)
{
	n_particles_++;
}

Particle::~Particle()
{
	n_particles_--;
}

void Particle::countParticles()
{
	if (n_particles_ < 2){
		cerr << "-- INFO -- il y a " << n_particles_ << " particule en mémoire"<< endl;
	}
	else
	{
		cerr << "-- INFO -- il y a " << n_particles_ << " particules en mémoire"<< endl;
	}
}

int Particle::getType()
{
	return type_;
}

void Particle::setType(int type)
{
	type_ = type;
}

Particle * Particle::getNext()
{
	return next_;
}

void Particle::setNext(Particle *next)
{
	next_=next;
}

int Particle::chooseInteractionType()
{
	int interactionType;
	double x = uniform_law();
		if (x<1)
			interactionType=0;
		else 
			interactionType=1;
	//energy_
	return interactionType;
}

double Particle::Parcours(){
	return 0;
}

double Particle::Propagation(double lambda){
	double L=0;
	L=gsl_ran_exponential(rng_, lambda);
	return L;
}

void Particle::Interaction(void){
	int interactionType = chooseInteractionType();
	switch (interactionType)	{		case 0:
			cerr << "-- DEBUG -- Photoelectric effect"<< endl;
			break;
		case 1:			cerr << "-- DEBUG -- Compton scattering"<< endl;			break;
		case 2:			cerr << "-- DEBUG -- Pair production"<< endl;	
			break;
	}
}


