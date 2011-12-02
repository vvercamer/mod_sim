#include "experiment.h"

Experiment::Experiment(double energy): topOfStack_(0)
{
	rng_ = random_init();
	source_ = new Source(rng_,energy);	
}

Experiment::~Experiment()
{
	Particle * particle;
	while( (particle = topOfStack_) != 0) {		topOfStack_ = particle->getNext();		delete particle;
	};
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
	topOfStack_ = source_->emitParticle();
	
	Particle* particle;
	int n=4;
	int i;	for (i = 0 ; i < n ; i++){		particle = new Particle(rng_,0,0);
		add2Stack(particle);
		particle->countParticles();
		showStack();
	}

	while (topOfStack_->getPrev() != 0){
		removeFromStack(topOfStack_);
		particle->countParticles();
		//cerr << "il y a " << n << " particules dans la piles"<< endl;
		n--;
		showStack();
	}

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
	Particle* current = topOfStack_;
	do{
			cout << current << endl;
			current=current->getPrev();
	}while(current != 0);
}

void Experiment::add2Stack(Particle * particle)
{
	topOfStack_ -> setNext(particle);
	particle -> setPrev(topOfStack_);
	topOfStack_ = particle;
}

void Experiment::removeFromStack(Particle * particle)
{
		topOfStack_ = particle->getPrev();
		topOfStack_ -> setNext(0);
		delete particle;
}

int Particle::n_particles_ = 0; //à déplacer plus tard.

