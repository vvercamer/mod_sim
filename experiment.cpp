#include "experiment.h"

Experiment::Experiment(){

}

Experiment::~Experiment(){
	
}

void Experiment::StartOfRun(int argc, char * argv[]){
//plus tard : initialiser l'enceinte, le collimateur et le détecteur	
}

void Experiment::EndOfRun(){

}

void Experiment::Event(){

}

Particle * Experiment::getStack(){
	return stack_;
}

int Particle::n_particles_ = 0; //à déplacer plus tard.

