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
	// Empty the stack (normaly already empty)
	Particle * particle;
	while( (particle = topOfStack_) != 0) {		topOfStack_ = particle->getNext();		delete particle;
	};
	delete topOfStack_;
	
	// Delete the random seed
	gsl_rng_free(rng_);
	
	// Delete the physical components
	delete detector_;
	delete source_;
	delete collimator_;
	
	// Delete the 
	
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

double Experiment::event(int sourceType)
{
	if(LogLevel>2) cerr << "\n-- DEBUG -- New event" << endl;	
	double scintillationEnergy = 0;

	sourceEmission emission = source_->emitParticle(sourceType);
	for(int i=0; i < emission.nParticlesEmitted; i++) {
		add2stack(emission.particlesEmitted[i]);
	}
	delete[] emission.particlesEmitted;

	while (topOfStack_ != 0){
		Particle* current = topOfStack_;
	//	showStack();

	//	cerr << "-- DEBUG -- Taking care of particle " << current << " energy : " << current->getEnergy() << endl;
		removeTopOfStack();
		int propagationResult = current->Propagation(collimator_,detector_,data);
		
		if (propagationResult == 2) {
			propagationResult = current->Propagation(collimator_,detector_,data);
		}
		
		if (propagationResult == 1) {
			interactionResult result = current->Interaction(data);
			scintillationEnergy += result.depositedEnergy;
		// Adding to the stack the particles resulting from previous interaction
			for (int i=0; i < result.nParticlesCreated; i++) {
				add2stack((Particle*)result.particlesCreated[i]);
			}
			delete[] result.particlesCreated;
		}
		
		delete current;
		current = 0;

	}
	if(LogLevel>2) cerr << "-- DEBUG -- Deposited energy : " << scintillationEnergy << " keV" << endl;
	if(LogLevel>2) cerr << "-- DEBUG -- Collected charges : " << detector_->photomultiplication(detector_->scintillation(scintillationEnergy)) << endl;
	
	double Fano=0.21;
	return (scintillationEnergy + gsl_ran_gaussian(rng_, sqrt(scintillationEnergy*Fano)));
//	return scintillationEnergy;
}

Particle * Experiment::getTopOfStack()
{
	return topOfStack_;
}

void Experiment::showStack()
{
	if(LogLevel>1) cerr << "-- INFO -- Show stack" << endl;
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
	if(LogLevel>1) cerr << "-- INFO -- there are "<< i << " particles in the stack" << endl;
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
