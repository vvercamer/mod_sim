#include "particle.h"

Particle::Particle(double a, double b, double c){
	
	x = a;
	y = b;
	z = c;
	n_particle++;
};

Particle::~Particle(){
	n_particle--;	
};


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

//double Particle::Parcours(){
// Instructions composant le corps de la fonction;
//};