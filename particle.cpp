#include "particle.h"

Particle::Particle(){
	n_particles_++;
};

Particle::~Particle(){
	n_particles_--;	
};

void Particle::count(void)
{
        cout << n_particles_ << " particules(s)" << endl;
}

int Particle::getType(void)
{
	return type_;
};

void Particle::setType(int type)
{
	type_ = type;
};



double Particle::Parcours(){
	return 0;
};

void Particle::Propagation(void){

};

void Particle::Interaction(void){

};
