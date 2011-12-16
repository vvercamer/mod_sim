#include "particle.h"

Particle::Particle(gsl_rng * rng, int type, Particle * next): rng_(rng), type_(type), next_(next)
{
	n_particles_++;
}

Particle::~Particle()
{
	n_particles_--;
}

void Particle::countParticles()
{
	if (n_particles_ < 2){
		cerr << "-- INFO -- il y a " << n_particles_ << " particule en mémoire"<< endl;
	}
	else
	{
		cerr << "-- INFO -- il y a " << n_particles_ << " particules en mémoire"<< endl;
	}
}

int Particle::getType()
{
	return type_;
}

void Particle::setType(int type)
{
	type_ = type;
}

Particle * Particle::getNext()
{
	return next_;
}

void Particle::setNext(Particle *next)
{
	next_=next;
}

int Particle::selectInteractionType(double*** data)
{
	int interactionType;
	double peNa, cNa, ppNa, peI, cI, ppI;
	double dataNorm=0;
	energy_=1.2; //à supprimer
	int idxData=0;
	while (energy_ > data[0][0][idxData] && idxData < (nLines-1)) {
		idxData++;
	}
	dataNorm = data[0][nColumns-1][idxData]+data[1][nColumns-1][idxData];
	if (dataNorm <= 0){
		cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
		exit(EXIT_FAILURE);
	}
		
	peNa = data[0][1][idxData]/dataNorm;
	cNa = data[0][1][idxData]/dataNorm;
	ppNa = data[0][1][idxData]/dataNorm;
	peI = data[0][1][idxData]/dataNorm;
	cI = data[0][1][idxData]/dataNorm;
	ppI = data[0][1][idxData]/dataNorm;
		
	cerr << "data[0][0]["<<idxData<<"] : " << data[0][0][idxData] <<endl;	
	cerr<<"NRJ "<<energy_<<endl;
	double x = uniform_law();
		
		if (x<=1) {
			
			interactionType=0;//Photoelectric Na
		}
/*		else if () {
			interactionType=1;//Compton Na
		}
		else if () {
			interactionType=2;//Pair Production Na
		}*/
/*		else if () {
			interactionType=1;//Compton Na
		}
		else if () {
			interactionType=2;//Pair Production Na
		}*/
	//energy_
		else {
			cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
			exit(EXIT_FAILURE);
		}
		return interactionType;
}

double Particle::Parcours(){
	return 0;
}

double Particle::Propagation(double lambda){
	double L=0;
	L=gsl_ran_exponential(rng_, lambda);
	return L;
}

void Particle::Interaction(double*** data){
	int interactionType = selectInteractionType(data);
	switch (interactionType)	{		case 0:
			cerr << "-- DEBUG -- Photoelectric effect"<< endl;
			break;
		case 1:			cerr << "-- DEBUG -- Compton scattering"<< endl;			break;
		case 2:			cerr << "-- DEBUG -- Pair production"<< endl;	
			break;
			
	}
}


