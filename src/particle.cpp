#include "particle.h"

Particle::Particle(gsl_rng * rng, double energy): rng_(rng), energy_(energy)
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
	int idxData=0;
	while (energy_ > data[0][0][idxData] && idxData < (nLines-1)) {
		idxData++;
	}
	dataNorm = (Na_A*(data[0][1][idxData]+data[0][2][idxData]+data[0][3][idxData])+I_A*(data[1][1][idxData]+data[1][2][idxData]+data[1][3][idxData]))/(Na_A+I_A);
	if (dataNorm <= 0){
		cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
		exit(EXIT_FAILURE);
	}
		
	cNa = Na_A*data[0][1][idxData]/(Na_A+I_A);
	peNa = Na_A*data[0][2][idxData]/(Na_A+I_A);
	ppNa = Na_A*data[0][3][idxData]/(Na_A+I_A);
	cI = I_A*data[1][1][idxData]/(Na_A+I_A);
	peI = I_A*data[1][2][idxData]/(Na_A+I_A);
	ppI = I_A*data[1][3][idxData]/(Na_A+I_A);
	
	/* //for debug
	cerr << "dataNorm : " << dataNorm <<endl;
	cerr << "sum p : " << (peNa+cNa+ppNa+cI+peI+ppI) <<endl;
	cerr << "NRJ " << energy_ << "keV" << endl;
	cerr << "data[0][0]["<<idxData<<"] : " << data[0][0][idxData] << "keV" <<endl;
	cerr << "cNa : " << cNa/dataNorm <<endl;
	cerr << "peNa : " << peNa/dataNorm <<endl;
	cerr << "ppNa : " << ppNa/dataNorm <<endl;
	cerr << "cI : " << cI/dataNorm <<endl;
	cerr << "peI : " << peI/dataNorm <<endl;
	cerr << "ppI : " << ppI/dataNorm <<endl;
	*/
	
	double x = uniform_law()*dataNorm;
			
		if (x>0 && x<=cNa) {
			interactionType=0;//Compton Na
		}
		else if (x>cNa && x<=(cNa+peNa)) {
			interactionType=1;//Photoelectric Na
		}
		else if (x>(cNa+peNa) && x<=(cNa+peNa+ppNa)) {
			interactionType=2;//Pair Production Na
		}
		else if (x>(cNa+peNa+ppNa) && x<=(cNa+peNa+ppNa+cI)) {
			interactionType=3;//Compton I
		}
		else if (x>(cNa+peNa+ppNa+cI) && x<=(peNa+cNa+ppNa+cI+peI)) {
			interactionType=4;//Photoelectric I
		}
		else if (x>(cNa+peNa+ppNa+cI+peI) && x<=dataNorm) {
			interactionType=5;//Pair Production I
		}
		else {
			cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
			exit(EXIT_FAILURE);
		}
		return interactionType;
}

double Particle::Parcours(){
	return 0;
}

double Particle::I_Photoelectric()
{
	// Determination of the energy of the photoelectron
	int i=0;
	double random;
	double electronEnergy = 0;
	while(electronEnergy == 0)
	{
		random = uniform_law();
		if (I_Shells[i] == 0)
			electronEnergy = energy_;
		else if (energy_ > I_Shells[i] && random < 0.9)
			electronEnergy = energy_ - I_Shells[i];
			
		i++;
	}
	return electronEnergy;
}

interactionResult Particle::I_Compton()
{
	double comptonEnergy=0;
	double thetaCompton=0;
	
	//EX'= EX / (1+(EX/mc2)(1-cosθ))
	comptonEnergy = energy_/(1+energy_/511*(1-cos(thetaCompton)))
	interactionResult result;
	result.nParticlesCreated = 1;
	result.depositedEnergy = energy_ - comptonEnergy;
	result.particlesCreated = new void * [result.nParticlesCreated];
	result.particlesCreated[0] = new Particle(rng_,comptonEnergy);
	
	return result;
}

double Particle::Propagation(double lambda){
	double L=0;
	L=gsl_ran_exponential(rng_, lambda);
	return L;
}

interactionResult Particle::Interaction(double*** data)
{
	
	interactionResult result;
	
	result.nParticlesCreated = 0;
	result.particlesCreated = 0;
	result.depositedEnergy = 0 ;
	
	int interactionType = selectInteractionType(data);
	switch (interactionType)	{		case 0:			cerr << "-- DEBUG -- Na Compton scattering"<< endl;			break;
		case 1:
			cerr << "-- DEBUG -- Na Photoelectric effect"<< endl;
			break;
		case 2:			cerr << "-- DEBUG -- Na Pair production"<< endl;	
			break;
		case 3:			cerr << "-- DEBUG -- I Compton scattering"<< endl;
			result=I_Compton();			break;
		case 4:
		{
			cerr << "-- DEBUG -- I Photoelectric effect"<< endl;
			result.depositedEnergy=I_Photoelectric();
			
			// Auger / Fluo
			
			double random = uniform_law();
			
			if(random < I_Auger)
			{
			// AUGER
			cout << "Auger" << endl;
			}
			else
			{
			// FLUO
			cout << "Fluo" << endl;
			}
		
			break;
		}
		case 5:			cerr << "-- DEBUG -- I Pair production"<< endl;	
			break;
		default:
			cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
			exit(EXIT_FAILURE);
			break;
			
	}
	
//	result.particlesCreated = new void * [result.nParticlesCreated];
//	result.particlesCreated[0] = new Particle(rng_,25);
	return result;
}


