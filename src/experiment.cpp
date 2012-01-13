#include "experiment.h"

Experiment::Experiment(sourceParameters sParam, collimatorParameters cParam, detectorParameters dParam): topOfStack_(0)
{
	rng_ = random_init();
	source_ = new Source(rng_, sParam);	
	collimator_ = new Collimator(cParam);
	detector_ = new Detector(dParam);

	// Loading Interaction Data
	int i,j = 0;
	data = new double ** [2];
	for(i = 0; i < 2; i++) {
	    data[i] = new double * [nColumns];
	    for(j = 0; j < nColumns; j++)
			data[i][j] = new double [nLines];
	}
	
	initData(data);

}

Experiment::~Experiment()
{
	Particle * particle;
	while( (particle = topOfStack_) != 0) {		topOfStack_ = particle->getNext();		delete particle;
	};
	
	delete detector_;
	delete source_;
	
	// Deleting Interaction Data
	int i,j = 0;
	for(i = 0; i < 2; i++) {
	    for(j = 0; j < nColumns; j++) {
	    	delete [] data[i][j];
			data[i][j] = 0;
		}
		delete [] data[i];
		data[i] = 0;
	}
	delete [] data;
	data = 0;
}

//void Experiment::StartOfRun(int argc, char * argv[])
//{
////plus tard : initialiser l'enceinte, le collimateur et le détecteur	
//}
//
//void Experiment::EndOfRun()
//{
//
//}

double Experiment::event()
{
	cerr << "\n-- INFO -- New event" << endl;	
	double scintillationEnergy = 0;
	add2stack(source_->emitParticle());

	while (topOfStack_ != 0){
		Particle* current = topOfStack_;
		//showStack();

		cerr << "-- DEBUG -- Taking care of particle " << current << endl;
		removeTopOfStack();
		//current->countParticles();

		if (current->Propagation(collimator_,detector_,data) == 1) {
			interactionResult result = current->Interaction(data);
			scintillationEnergy += result.depositedEnergy;
		// Adding to the stack the particles resulting from previous interaction
			for (int i=0; i < result.nParticlesCreated; i++)
				add2stack((Particle*)result.particlesCreated[i]);
		}
		else {
			cerr << "-- DEBUG -- The particle got out the experiment !" << endl;
		}
		
		delete current;
		current = 0;
		


	}
	cerr << "-- DEBUG -- Deposited energy : " << scintillationEnergy << " keV" << endl;
	cerr << "-- DEBUG -- Collected charges : " << detector_->photomultiplication(detector_->scintillation(scintillationEnergy)) << endl;
	
	double Fano=0.2;
//	cerr << "Delta E = " << gsl_ran_gaussian(rng_, scintillationEnergy*2.35*sqrt(Fano)) << endl;
	cerr << "Sigma   = " << sqrt(scintillationEnergy)*2.35*Fano << endl;
	cerr << "Delta E = " << gsl_ran_gaussian(rng_, sqrt(scintillationEnergy)*2.35*Fano) << endl;
	return (scintillationEnergy);//*(1 + gsl_ran_gaussian(rng_, scintillationEnergy*Fano)));
}

Particle * Experiment::getTopOfStack()
{
	return topOfStack_;
}

void Experiment::showStack()
{
	cerr << "-- INFO -- Show stack" << endl;
	int i=0;
	if(topOfStack_ != 0) {
		Particle* current = topOfStack_;
		do{
				cerr << current << endl;
				current=current->getNext();
				i++;
		}while(current != 0);
	}
	else {
		cerr << "-- ERROR -- Attempted to show an empty stack !" << endl;
		exit(EXIT_FAILURE);
	}
	cerr << "-- INFO -- there are "<< i << " particles in the stack" << endl;
}

void Experiment::add2stack(Particle* particle)
{
	particle -> setNext(topOfStack_);
	topOfStack_ = particle;
}

void Experiment::removeTopOfStack()
{
	if(topOfStack_ != 0) {
		Particle * currentFirst = topOfStack_;
		if(currentFirst -> getNext() != 0) {
			topOfStack_ = currentFirst -> getNext();
			currentFirst -> setNext(0);
		}
		else {
			topOfStack_ = 0;
		}
	}
	else {
		cerr << "-- ERROR -- Attempted to remove a particule from an empty stack !" << endl;
		exit(EXIT_FAILURE);
	}
}

int Particle::n_particles_ = 0; //à déplacer plus tard.

