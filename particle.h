#ifndef _PARTICLE_H_INCLUDED
#define _PARTICLE_H_INCLUDED

#include <iostream>
using namespace std;

class Particle {
private : // définition les données membres de la classe
	static int n_particles;
	int type;
	double x, y, z;
	double theta, phi;
	double impulse;
	double energy;
public : // définition les fonctions membres de la classe
	Particle(double = 0.0, double = 0.0, double = 0.0);
	~Particle();
	void Type(int t){type = t;};
	int Type(){return(type);};
	double getX(){return(x);};
	double getY(){return(y);};
	double getZ(){return(z);};
	void setX(double a){x=a;};
	void setY(double b){y=b;};
	void setZ(double c){z=c;};
	void count (void);
	double Parcours(void);
	void Propagation(void);
	void Interaction(void);
};

#endif
