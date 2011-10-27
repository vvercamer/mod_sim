#ifndef _PARTICLE_H_INCLUDED
#define _PARTICLE_H_INCLUDED

#include <vector> //http://www.fredosaurus.com/notes-cpp/stl-containers/vector/header-vector.html
#include <iostream>
using namespace std;

class Particle {
private : // définition les données membres de la classe
	static int n_particles_;
	int type_;
	double theta_, phi_;
	vector<double> position_;
	vector<double> impulse_;
	double energy_;
	Particle *next_;
	Particle *prev_;
	
public : // définition les fonctions membres de la classe
	Particle();
	~Particle();
	int getType(void);
	void setType(int);
//	void setPosition(){};
	void count(void);
	double Parcours(void);
	void Propagation(void);
	void Interaction(void);
};

#endif
