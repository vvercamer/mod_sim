#ifndef _DETECTOR_H_INCLUDED
#define _DETECTOR_H_INCLUDED

#include <iostream>
using namespace std;

class Detector {
private :
	static const double eta_ = 0.04; //η  ~  4%  (taux  de  luminescence  du  scintillateur = η*ξ)
	//η : Rendement = 30% (nombre de paires électron-trou créées par un électron)
	//ξ : Coefficient de luminescence = 13% (proportion d’énergie transformée en scintillation).
	static const double QE_ = 0.11; //QE ~ 11% (efficacité quantique de la photocathode du multiplicateur
	static const double CE_ = 0.95; //CE ~  95%  (efficacité  de  collection  de  l’électron  de  conversion  par  la  première dynode
	double nDynodes_; // 8-10  étages d’amplification (dynodes)
	double *g_; //gi ~ 3 – 4 (gain de chacune des dynodes). 
	int Z_;
	int A_;
	static const double density_ = 3.67; //en kg/m3 ou g/cm3
		
public :
	Detector(int);
	~Detector();
	double getDensity();
};


#endif