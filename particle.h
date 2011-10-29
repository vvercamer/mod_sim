#ifndef _PARTICLE_H_INCLUDED
#define _PARTICLE_H_INCLUDED

//#include <vector> //http://www.fredosaurus.com/notes-cpp/stl-containers/vector/header-vector.html
#include <iostream>
using namespace std;

// définition des types
#define PHOTON 0
#define ELECTRON 1


class Particle {
private : // définition les données membres de la classe
	static int n_particles_;
	int type_;
	double theta_, phi_;
	double position_[3];
	double impulse_[3];
	double energy_;
	Particle *next_;
	Particle *prev_;
	
public : // définition les fonctions membres de la classe
	Particle(int, Particle *);
	~Particle();
	int getType();
	void setType(int);
//	void setPosition(){};
	Particle* getNext();	void setNext(Particle*);
	Particle* getPrev();	void setPrev(Particle*);
	void countParticles();
	double Parcours();
	void Propagation();
	void Interaction();
};

#endif
