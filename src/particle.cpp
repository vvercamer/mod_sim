#include "particle.h"

Particle::Particle(gsl_rng * rng, double energy): rng_(rng), energy_(energy)
{
	n_particles_++;
}

Particle::~Particle()
{
	n_particles_--;
}

// private functions

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

double compton_distrib(double x,double ksi){
//	double r=2.81794092e-15;pow(r,2)*
	return 1/pow(1+ksi*(1-cos(x)),2)*(1+pow(cos(x),2)+pow(ksi*(1-cos(x)),2)/(1+ksi*(1-cos(x))))/2;
}

void Particle::PhotoElectric(int atom, interactionResult * result)
{
	const double * Shells = 0;
  
	if (atom == 0){
		Shells = Na_Shells;
	}
	else if (atom == 1){
		Shells = I_Shells;
	}
		
	// Determination of the energy of the photoelectron
	int i=-1;
	double random;
	double electronEnergy = 0;
	while(electronEnergy == 0){
		i++;
		random = uniform_law();
      
		if (Shells[i] == 0)
			electronEnergy = energy_;
		else if (energy_ > Shells[i] && random < 0.9)
			electronEnergy = energy_ - Shells[i];
    }

	result->depositedEnergy = electronEnergy;

	// Auger / Fluo
	random = uniform_law();
  
	if(random < I_Auger){
		// AUGER
		cerr << "-- DEBUG -- Auger" << endl;
    }
  
	else{
		// FLUO
      cerr << "-- DEBUG -- Fluo " << endl;
      
      // K alpha
	if ( i == 0 ){
		cerr << " (K alpha) " << endl;
		random = uniform_law();
		double hnuFluo;
		if (random <= 0.5)
			hnuFluo = I_Shells[0] - I_Shells[2]; // K alpha 1
		else
			hnuFluo = I_Shells[0] - I_Shells[3]; // K alpha 2
		
		result->nParticlesCreated = 1;
		result->particlesCreated = new void * [result->nParticlesCreated];
		result->particlesCreated[0] = new Particle(rng_,hnuFluo);
	}
      
      // not K
	else
		cerr << endl << "Ignoring fluorescence process (layer with a vacancy =/= K)" << endl;
	}
}

void Particle::Compton(interactionResult* result)
{
	double comptonEnergy=0;
	double thetaCompton=0;
	double ksi=energy_/511; // 511keV electron energy
	thetaCompton=parametric_arbitrary_law(compton_distrib,ksi,0,M_PI,1);

	comptonEnergy = energy_/(1+ksi*(1-cos(thetaCompton))); 
	
	cerr<< "-- DEBUG -- intialEnergy : " << this->energy_ << endl;
	cerr<< "-- DEBUG -- comptonEnergy : " << comptonEnergy << endl;
	
	result->nParticlesCreated = 1;
	result->depositedEnergy = energy_ - comptonEnergy;
	result->particlesCreated = new void * [result->nParticlesCreated];
	result->particlesCreated[0] = new Particle(rng_,comptonEnergy);
}

// public functions

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
			Compton(&result);			break;
		case 4:
		{
			cerr << "-- DEBUG -- I Photoelectric effect"<< endl;
			PhotoElectric(1, &result);
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


