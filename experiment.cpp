#include "experiment.h"

Experiment::Experiment()
{
	topOfStack_=0;
	source_=new Source;
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
	Particle* current = source_->emitParticle();
	topOfStack_=current;
		
//	cout << current->getType() << endl;
	showStack();
	
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

//void Experience:: AddTrack(int Type, int Charge, float Energy)
//{//	Particle * Track = new Particule();
//	Track -> Next( firsttrack);//	if (firsttrack) firsttrack -> Prev(Track);
//	firsttrack = Track;//}

int Particle::n_particles_ = 0; //à déplacer plus tard.

