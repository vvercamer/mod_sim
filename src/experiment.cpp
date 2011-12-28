#include "experiment.h"

Experiment::Experiment(double energy, double sourceSigma): topOfStack_(0)
{
	rng_ = random_init();
	source_ = new Source(rng_, energy, sourceSigma);	
	detector_ = new Detector();

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

void Experiment::event()
{
	cerr << "\n-- INFO -- New event" << endl;	
	double lambda = 1; // en m
	double mu = 1;
	double scintillationEnergy = 0;
	add2stack(source_->emitParticle());

	while (topOfStack_ != 0){
		Particle* current = topOfStack_;
		//showStack();

		cerr << "-- DEBUG -- Taking care of particle " << current << endl;
		removeTopOfStack();
		//current->countParticles();
		

		if ((mu = detector_->getDensity()) == 0){//*detector_->getCrossSection(current->getEnergy,NaI);
			cerr << "-- ERROR -- Attempted to divide by ZERO (mu = 1/lambda) !" << endl;
			exit(EXIT_FAILURE);
		}
		lambda = 1/mu;
		current->Propagation(lambda);
	//	cerr << "-- DEBUG -- distance de propagation : " << current->Propagation(lambda) << endl;
	
		interactionResult result = current->Interaction(data);
		scintillationEnergy += result.depositedEnergy;

		delete current;
		current = 0;
		
		// Adding to the stack the particles resulting from previous interaction
		for (int i=0; i < result.nParticlesCreated; i++)
			add2stack((Particle*)result.particlesCreated[i]);

	}
	cerr << "--DEBUG-- Deposited energy : " << scintillationEnergy << endl;
	cout << scintillationEnergy << endl;
	cerr << "collected charges : " << detector_->photomultiplication(detector_->scintillation(scintillationEnergy)) << endl;
}

Particle * Experiment::getTopOfStack()
{
	return topOfStack_;
}

void Experiment::setTopOfStack(Particle* topOfStack){
	topOfStack_=topOfStack;
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

void Experiment::add2stack(Particle * particle)
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

