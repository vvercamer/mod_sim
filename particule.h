#ifndef _PARTICULE_H_INCLUDED
#define _PARTICULE_H_INCLUDED

class Particule {
private : // définition les données membres de la classe
	int type;
	double x, y, z;
	double theta, phi;
	double impulse;
	double energy;
public : // définition les fonctions membres de la classe
	Particule();
	~Particule();
	void Type(int t){type = t;};
	int Type(){return(type);};
	double getX(){return(x);};
	double getY(){return(y);};
	double getZ(){return(z);};
	void setX(double x);
	void setY(double y);
	void setZ(double z);
//	double Parcours();
};

#endif
