#include "particle.h"

Particle::Particle(int type, Particle * prev): type_(type), next_(0), prev_(prev)
{
	n_particles_++;
}

Particle::~Particle()
{
	n_particles_--;
	
}

void Particle::countParticles(void)
{
        cerr << n_particles_ << " particules(s)" << endl;
}

int Particle::getType(void)
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
