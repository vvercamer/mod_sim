#ifndef _DETECTOR_H_INCLUDED
#define _DETECTOR_H_INCLUDED

#include <iostream>
using namespace std;

class Detector {
private :
	double eta_;
	double QE_;
	double CE_;
	double nDynodes_;
	double *g_;
	int Z_;
	int A_;
	int pressure_;
	int density_;
		
public :
	Detector(int);
	~Detector();
};

#endif


//Où,//η  ~  4%  (taux  de  luminescence  du  scintillateur)//QE ~ 11% (efficacité quantique de la photocathode du multiplicateur//CE ~  95%  (efficacité  de  collection  de  l’électron  de  conversion  par  la  première  //dynode)//gi ~ 3 – 4 (gain de chacune des dynodes). Un photomiltiplicateur possède//communément entre huit à dix  étage  d’amplification (dynodes)//Travail ://Créer un fichier   d’entête   « Detecteur.h » avec toutes les données qui vous semblent appartenir à un objet de cette classe, par exemple, le nombre de masse et de charge du milieu, la pression, la densité ... ainsi que les prototypes des fonctions membres de cette classe. Dans un second fichier « Detecteur.cpp » programmer le corps des fonctions membres.