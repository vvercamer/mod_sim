#include "detector.h"

Detector::Detector(int nDynodes) : nDynodes_(nDynodes)
{
	cerr << "-- INFO -- Constructeur : détecteur à " << nDynodes_ << " dynodes\n";
	if (nDynodes_ > 0) {
		g_ = new double [nDynodes];
		memset(g_, 0, nDynodes * sizeof(double));
	}
	else {
		cerr << "-- ERROR -- il faut au moins une dynode dans le détecteur" << endl;
		exit(EXIT_FAILURE);
	}
}

Detector::~Detector()
{
	if (g_ != NULL) {
		delete [] g_;
	}
}

double Detector::getDensity()
{
	return density_;
}


//Photo-electrique ://PHOTON + Na => e- + Na+*
//PHOTON + I => e- + I+*
//
//Compton ://PHOTON + Na => X'+ e- + Na+*
//PHOTON + I => X'+ e- + I+*
////Création de paires ://PHOTON + Na => e+ + e- + Na//PHOTON + I => e+ + e- + I