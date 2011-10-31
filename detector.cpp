#include "detector.h"

Detector::Detector(int nDynodes) : nDynodes_(nDynodes)
{
	cout << "Constructeur a " << nDynodes_ << " elements\n";
	if (nDynodes_ > 0) {
		g_ = new double [nDynodes];
		memset(g_, 0, nDynodes * sizeof(double));
	}
	else {
		cerr << "il faut au moins une dynode dans le détecteur" << endl;
	}
}

Detector::~Detector()
{
	cout << "Destructeur : " << nDynodes_ << " elements\n";
	if (g_ != NULL) {
		delete [] g_;
	}
}


//Photo-electrique ://PHOTON + Na => e- + Na+*
//PHOTON + I => e- + I+*
//
//Compton ://PHOTON + Na => X'+ e- + Na+*
//PHOTON + I => X'+ e- + I+*
////Création de paires ://PHOTON + Na => e+ + e- + Na//PHOTON + I => e+ + e- + I