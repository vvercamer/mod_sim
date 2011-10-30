#ifndef _DETECTOR_H_INCLUDED
#define _DETECTOR_H_INCLUDED

#include <iostream>
using namespace std;

class Detector {
private :
	double eta_; //η  ~  4%  (taux  de  luminescence  du  scintillateur)
	double QE_; //QE ~ 11% (efficacité quantique de la photocathode du multiplicateur
	double CE_; //CE ~  95%  (efficacité  de  collection  de  l’électron  de  conversion  par  la  première dynode
	double nDynodes_; // 8-10  étages d’amplification (dynodes)
	double *g_; //gi ~ 3 – 4 (gain de chacune des dynodes). 
	int Z_;
	int A_;
	int pressure_;
	int density_;
		
public :
	Detector(int);
	~Detector();
};

#endif