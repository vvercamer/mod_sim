#include "source.h"

Source::Source()
{
	
}

Source::~Source()
{
	
}

Particle* Source::emitParticle()
{
	//fonction qui aura pour but de créer la particule primaire et de retourner, lors de son appel, la valeur du pointeur de l’objet de la classe particule ainsi généré.
	Particle* primary = new Particle(0,0);	
	return primary;
}
