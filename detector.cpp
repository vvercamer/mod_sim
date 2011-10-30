#include "detector.h"

Detector::Detector(int nDynodes) : nDynodes_(nDynodes)
{
	cout << "Constructeur a " << nDynodes_ << " elements\n";
	if (nDynodes_ > 0) {
		g_ = new double [nDynodes_];
		memset(g_, 0, nDynodes_ * sizeof(double));
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