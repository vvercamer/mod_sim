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
	double cNa, peNa, ppNa, cI, peI, ppI;
	double dataNorm=0;
	energy_=1.2; //à supprimer
	int idxData=0;
	while (energy_ > data[0][0][idxData] && idxData < (nLines-1)) {
		idxData++;
	}
	dataNorm = (Na_A*(data[0][1][idxData]+data[0][2][idxData]+data[0][3][idxData])+I_A*(data[1][1][idxData]+data[1][2][idxData]+data[1][3][idxData]))/(Na_A+I_A);
	if (dataNorm <= 0){
		cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
		exit(EXIT_FAILURE);
	}
		
	cNa = Na_A*data[0][1][idxData]/(Na_A+I_A)/dataNorm;
	peNa = Na_A*data[0][2][idxData]/(Na_A+I_A)/dataNorm;
	ppNa = Na_A*data[0][3][idxData]/(Na_A+I_A)/dataNorm;
	cI = I_A*data[1][1][idxData]/(Na_A+I_A)/dataNorm;
	peI = I_A*data[1][2][idxData]/(Na_A+I_A)/dataNorm;
	ppI = I_A*data[1][3][idxData]/(Na_A+I_A)/dataNorm;
	
/*	cerr << "dataNorm : " << dataNorm <<endl;
	cerr << "sum p : " << (peNa+cNa+ppNa+cI+peI+ppI) <<endl;
	cerr << "data[0][0]["<<idxData<<"] : " << data[0][0][idxData] <<endl;
	cerr << "cNa : " << cNa <<endl;
	cerr << "peNa : " << peNa <<endl;
	cerr << "ppNa : " << ppNa <<endl;
	cerr << "cI : " << cI <<endl;
	cerr << "peI : " << peI <<endl;
	cerr << "ppI : " << ppI <<endl;*/
	cerr<<"NRJ "<<energy_<<endl;
	double x = uniform_law();
	
	cerr<<"x= "<<x<<endl;
		
		if (x<=cNa) {
			interactionType=0;//Compton Na
		}
		else if (x>cNa && x<=(cNa+peNa)) {
			interactionType=1;//Photoelectric Na
		}
		else if (x>(cNa+peNa) && x<=(cNa+peNa+ppNa)) {
			interactionType=2;//Pair Production Na
		}
		else if (x>(cNa+peNa+ppNa) && x<=(cNa+peNa+ppNa+cI)) {
			interactionType=3;//Compton Na
		}
		else if (x>(cNa+peNa+ppNa+cI) && x<=(peNa+cNa+ppNa+cI+peI)) {
			interactionType=4;//Photoelectric Na
		}
		else if (x>(cNa+peNa+ppNa+cI+peI) && x<=1) {
			interactionType=5;//Pair Production Na
		}
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
	switch (interactionType)	{		case 0:			cerr << "-- DEBUG -- Na Compton scattering"<< endl;			break;
		case 1:
			cerr << "-- DEBUG -- Na Photoelectric effect"<< endl;
			break;
		case 2:			cerr << "-- DEBUG -- Na Pair production"<< endl;	
			break;
		case 3:			cerr << "-- DEBUG -- I Compton scattering"<< endl;			break;
		case 4:
			cerr << "-- DEBUG -- I Photoelectric effect"<< endl;
			break;
		case 5:			cerr << "-- DEBUG -- I Pair production"<< endl;	
			break;
			
	}
}


