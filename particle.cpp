#include "particle.h"

Particle::Particle(double a, double b, double c){
	
	x = a;
	y = b;
	z = c;
	n_particles++;
};

Particle::~Particle(){
	n_particles--;	
};

void Particle::count(void)
{
        cout << n_particles << " particules(s)" << endl;
}

//void Particle::setX(double a){
//	x = a;
//}
//
//void Particle::setY(double a){
//	y = a;
//}

//void Particle::setZ(double a){
//	z = a;
//}

double Particle::Parcours(){

return 0;
};

void Particle::Propagation(void){

};

void Particle::Interaction(void){

};