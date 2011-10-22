#include "particule.h"

Particule::Particule(){
	x = 0;
	y = 0;
	z = 0;
};

Particule::~Particule(){
	
};


void Particule::setX(double a){
	x = a;
}

void Particule::setY(double a){
	y = a;
}

void Particule::setZ(double a){
	z = a;
}

//double Particule::Parcours(){
// Instructions composant le corps de la fonction;
//};