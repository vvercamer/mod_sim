#include "particle.h"

Particle::Particle(int type, Particle * prev): type_(type), next_(0), prev_(prev)
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
		cerr << "il y a " << n_particles_ << " particule dans la piles"<< endl;
	}
	else
	{
		cerr << "il y a " << n_particles_ << " particules dans la piles"<< endl;
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

Particle* Particle::getPrev()
{
	return prev_;
}

void Particle::setPrev(Particle *prev)
{
	prev_=prev;
}

double Particle::Parcours(){
	return 0;
}

void Particle::Propagation(void){

}

void Particle::Interaction(void){

}
