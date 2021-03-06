#include "particle.h"
/*
Particle::Particle(gsl_rng * rng, double energy): rng_(rng), energy_(energy)
{
	n_particles_++;
}
*/
Particle::Particle(gsl_rng * rng, double energy, double theta, double position[2]):
rng_(rng), energy_(energy), theta_(theta)
{
	position_[0]=position[0];
	position_[1]=position[1];
}

Particle::~Particle()
{
}

// private functions

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
	int idxData = nLines-1;
	while (energy_ < data[0][0][idxData] && idxData > 0) {
		idxData--;
	}

	dataNorm = (Na_A*(data[0][1][idxData]+data[0][2][idxData]+data[0][3][idxData])+I_A*(data[1][1][idxData]+data[1][2][idxData]+data[1][3][idxData]))/(Na_A+I_A);

	if (dataNorm <= 0) {
		cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
		exit(EXIT_FAILURE);
	}

	cNa = Na_A*data[0][1][idxData]/(Na_A+I_A);
	peNa = Na_A*data[0][2][idxData]/(Na_A+I_A);
	ppNa = Na_A*data[0][3][idxData]/(Na_A+I_A);
	cI = I_A*data[1][1][idxData]/(Na_A+I_A);
	peI = I_A*data[1][2][idxData]/(Na_A+I_A);
	ppI = I_A*data[1][3][idxData]/(Na_A+I_A);
	
	 //for debuging
/*	cerr << "dataNorm : " << dataNorm <<endl;
	cerr << "sum p : " << (peNa+cNa+ppNa+cI+peI+ppI) <<endl;
	cerr << "NRJ " << energy_ << "keV" << endl;
	cerr << "data[0][0]["<<idxData<<"] : " << data[0][0][idxData] << "keV" <<endl;
	cerr << "cNa : " << cNa <<endl;
	cerr << "peNa : " << peNa <<endl;
	cerr << "ppNa : " << ppNa <<endl;
	cerr << "cI : " << cI <<endl;
	cerr << "peI : " << peI <<endl;
	cerr << "ppI : " << ppI <<endl;
*/	
	
	double x = uniform_law()*dataNorm;
		
	if (x>=0 && x<=cNa) {
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

double compton_distrib(double x,double ksi) {
	return 1/pow(1+ksi*(1-cos(x)),2)*(1+pow(cos(x),2)+pow(ksi*(1-cos(x)),2)/(1+ksi*(1-cos(x))))/2;
}

void Particle::PhotoElectric(int atom, interactionResult * result)
{
	const double * Shells = 0;
	double probaAuger = 0;
	if (atom == 0){
		Shells = Na_Shells;
		probaAuger = Na_Auger;
	}
	else if (atom == 1){
		Shells = I_Shells;
		probaAuger = I_Auger;
	}
	else {
		cerr << "-- ERROR -- Problem during Photoelectric" << endl;
		exit(EXIT_FAILURE);
	}

		
	// Determination of the energy of the photoelectron
	int i=-1;
	double random=0;
	double electronEnergy = 0;
	while (electronEnergy == 0) {
		i++;
		random = uniform_law();
      
		if (Shells[i] == 0)
			electronEnergy = energy_;
		else if (energy_ >= Shells[i] && random < 0.9)
			electronEnergy = energy_ - Shells[i];
    }

	result->depositedEnergy += electronEnergy;

	AugerFluo(atom,result,Shells,probaAuger,i);
}

void Particle::AugerFluo(int atom, interactionResult * result, const double * Shells, double probaAuger, int emptyShell)
{
	double random = uniform_law();
	if(Shells[emptyShell] == 0)
		return;

	// SODIUM
	if(atom == 0) {
	}

	// IODINE
	if(atom == 1) {
		if(random < probaAuger) {
			// AUGER
			if(LogLevel>2) cerr << "-- DEBUG -- Auger" << endl;

			if ( emptyShell == 0 ) {
				random = uniform_law()*3+0.01;
				int shell = ceil(random);
				result->depositedEnergy += Shells[0] - 2*Shells[shell];
				AugerFluo(atom,result,Shells,probaAuger,shell);
				AugerFluo(atom,result,Shells,probaAuger,shell);
			}
		
			else if( (emptyShell == 1) || (emptyShell == 2) || (emptyShell == 3)) {
				result->depositedEnergy += Shells[emptyShell] - 2*Shells[4];
				AugerFluo(atom,result,Shells,probaAuger,4);
				AugerFluo(atom,result,Shells,probaAuger,4);
			}
		
			else if( emptyShell == 4 ) {
				result->depositedEnergy += Shells[4];
			}

		}
		
		else {
			// FLUO
			if(LogLevel>2) cerr << "-- DEBUG -- Fluo " ;

			// K layer
			if ( emptyShell == 0 ) {
				random = uniform_law();
				double hnuFluo;
				if (random <= 0.5) {
					if(LogLevel>2) cerr << "-- DEBUG -- (K alpha1) " << endl;
					hnuFluo = I_Shells[0] - I_Shells[2]; // K alpha 1
				}
				else {
					if(LogLevel>2) cerr << "-- DEBUG -- (K alpha2) " << endl;
					hnuFluo = I_Shells[0] - I_Shells[3]; // K alpha 2
				}
		
				double theta=uniform_law()*2*M_PI;
		
				result->nParticlesCreated += 1;
				void ** save = new void * [result->nParticlesCreated];
				for(int i = 0; i < result->nParticlesCreated - 1; i++)
					save[i] = result->particlesCreated[i];
				delete result->particlesCreated;
				result->particlesCreated = save;
				result->particlesCreated[result->nParticlesCreated-1] = new Particle(rng_,hnuFluo,theta,position_);

			}

			// L layer
			else if( (emptyShell == 1) || (emptyShell == 2) || (emptyShell == 3)) {
				if(LogLevel>2) cerr << "-- DEBUG -- (L alpha) " << endl;
				double hnuFluo;
				hnuFluo = I_Shells[emptyShell] - I_Shells[4]; // L alpha
		
				double theta=uniform_law()*2*M_PI;
		
				result->nParticlesCreated += 1;
				void ** save = new void * [result->nParticlesCreated];
				for(int i = 0; i < result->nParticlesCreated - 1; i++)
					save[i] = result->particlesCreated[i];
				delete result->particlesCreated;
				result->particlesCreated = save;
				result->particlesCreated[result->nParticlesCreated-1] = new Particle(rng_,hnuFluo,theta,position_);
			}
		
			// M layer
			else if(emptyShell == 4) {
				if(LogLevel>2) cerr << "-- DEBUG -- (M alpha) " << endl;
				double hnuFluo;
				hnuFluo = I_Shells[emptyShell]; // M alpha
		
				double theta=uniform_law()*2*M_PI;
		
				result->nParticlesCreated += 1;
				void ** save = new void * [result->nParticlesCreated];
				for(int i = 0; i < result->nParticlesCreated - 1; i++)
					save[i] = result->particlesCreated[i];
				delete result->particlesCreated;
				result->particlesCreated = save;
				result->particlesCreated[result->nParticlesCreated-1] = new Particle(rng_,hnuFluo,theta,position_);
			}
		}
	}
}

void Particle::Compton(interactionResult* result)
{
	double ksi = energy_/511; // 511keV electron energy
	double thetaCompton = sign_rand()*parametric_arbitrary_law(compton_distrib,ksi,0,M_PI,1);
	double comptonEnergy = energy_/(1+ksi*(1-cos(thetaCompton))); 



	double theta = theta_ + thetaCompton;
/*	while (theta>2*M_PI)
		theta -= 2*M_PI;
	while (theta<0)
		theta += 2*M_PI;
*/

	if (thetaCompton >= 0) {
		result->nParticlesCreated = 1;
		result->particlesCreated = new void * [result->nParticlesCreated];
		result->particlesCreated[0] = new Particle(rng_,comptonEnergy,theta,position_);
	}
	else {
		result->nParticlesCreated = 0;
	}
	result->depositedEnergy += energy_ - comptonEnergy;
	
	/*if (uniform_law() < 0.3){
		result->depositedEnergy = 0;
	}
	*/
}

void Particle::PairProduction(interactionResult* result)
{
	double theta = uniform_law()*M_PI;
	result->nParticlesCreated = 2;
	result->depositedEnergy += energy_ - 1022;
	result->particlesCreated = new void * [result->nParticlesCreated];
	result->particlesCreated[0] = new Particle(rng_,511,theta,position_);
	result->particlesCreated[1] = new Particle(rng_,511,theta+M_PI,position_);
}

// public functions

double Particle::Propagation(Collimator* collimator, Detector* detector, double*** data)
{
	//Propagation	--------	
	int idxData = nLines-1;
	while (energy_ < data[0][0][idxData] && idxData > 0 ) {
		idxData--;
	}
	
	double mu = detector->getDensity() * data[0][4][idxData];
	if (mu == 0) { // en cm-1
		cerr << "-- ERROR -- Attempted to divide by ZERO (mu = 1/lambda) !" << endl;
		exit(EXIT_FAILURE);
	}
	
	double L = exp_rand(mu); 
//	double L = gsl_ran_exponential(rng_, 1/mu);
	
	if ((detector->isIn(position_[0],position_[1])) && (detector->isIn(position_[0]+L*cos(theta_),position_[1]+L*sin(theta_)))) {
		position_[0] += L*cos(theta_);
		position_[1] += L*sin(theta_);
		return 1;
		}
	// else if particle is in detector but gets out
	else if (detector->isIn(position_[0],position_[1])) {
		return 0;
	}
	// else if particle is not in the detector
	else {
		if(cos(theta_) <= 0)
			return 0;
		
		double yIntersec = 0;
		
		// if it's before collimator
		if(position_[0] <= collimator->getX()) {
			yIntersec = position_[1] + (collimator->getX() - position_[0])*tan(theta_);
			
			// if it doesn't get through collimator
			if((cos(theta_) < 0) || ((yIntersec < (collimator->getY() - (collimator->getDiameter())/2)) 
						 || (yIntersec > (collimator->getY() + (collimator->getDiameter())/2)))) {
				return 0;
			}
		}
		
		// if particle is after collimator or it got through collimator
		yIntersec = position_[1] + (detector->getX() - position_[0])*tan(theta_);
		// if particle doesn't reach the detector
		if((cos(theta_) < 0) || ((yIntersec < (detector->getY() - (detector->getDiameter())/2)) 
					 || (yIntersec > (detector->getY() + (detector->getDiameter())/2)))) {
			return 0;
		}
		
		if (detector->isIn(detector->getX() - detector->getWidth()/2,
			position_[1]+(detector->getX() - detector->getWidth() - position_[0])*tan(theta_)) == 1) {
			position_[0] = detector->getX() - detector->getWidth()/2;
			position_[1] = position_[1] + (detector->getX() - detector->getWidth() - position_[0])*tan(theta_);
			return 2;
		}
		else if (detector->isIn(detector->getX() + detector->getWidth()/2,
			position_[1]+(detector->getX() + detector->getWidth() - position_[0])*tan(theta_)) == 1) {
			position_[0] = detector->getX() + detector->getWidth()/2;
			position_[1] = position_[1]+(detector->getX() + detector->getWidth() - position_[0])*tan(theta_);
			return 2;
		}
		else if (detector->isIn(position_[0]+(detector->getY() - detector->getDiameter()/2 - position_[1])/tan(theta_),
			detector->getY() - detector->getDiameter()/2) == 1) {
			position_[0] = position_[0] + (detector->getY() - detector->getDiameter()/2 - position_[1])/tan(theta_);
			position_[1] = detector->getY() - detector->getDiameter()/2 == 1;
			return 2;
		}
		else if (detector->isIn(position_[0]+(detector->getY() + detector->getDiameter()/2 - position_[1])/tan(theta_),
			detector->getY() + detector->getDiameter()/2) == 1) {
			position_[0] = position_[0] + (detector->getY() + detector->getDiameter()/2 - position_[1])/tan(theta_);
			position_[1] = detector->getY() + detector->getDiameter()/2 ;
			return 2;
		}
		else {
			return 0;
		}
	}
}

interactionResult Particle::Interaction(double*** data)
{
	
	interactionResult result;
	
	result.nParticlesCreated = 0;
	result.particlesCreated = 0;
	result.depositedEnergy = 0;
	
	int interactionType = selectInteractionType(data);
	switch (interactionType) {		case 0:			if(LogLevel>2) cerr << "-- DEBUG -- Na Compton scattering"<< endl;
			Compton(&result);
			break;
		case 1:
			if(LogLevel>2) cerr << "-- DEBUG -- Na Photoelectric effect"<< endl;
			PhotoElectric(0, &result);
			break;
		case 2:			if(LogLevel>2) cerr << "-- DEBUG -- Na Pair production"<< endl;
			PairProduction(&result);
			break;
		case 3:			if(LogLevel>2) cerr << "-- DEBUG -- I Compton scattering"<< endl;
			Compton(&result);			break;
		case 4:
			if(LogLevel>2) cerr << "-- DEBUG -- I Photoelectric effect"<< endl;
			PhotoElectric(1, &result);			
			break;
		case 5:			if(LogLevel>2) cerr << "-- DEBUG -- I Pair production"<< endl;	
			PairProduction(&result);
			break;
		default:
			if(LogLevel>2) cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
			exit(EXIT_FAILURE);
			break;		
	}

	return result;
}



