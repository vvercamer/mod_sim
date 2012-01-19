#include "source.h"

Source::Source(gsl_rng * rng, sourceParameters parameters):
rng_(rng), energy_(parameters.energy)
{
	position_[0]=parameters.position[0];
	position_[1]=parameters.position[1];
}

Source::~Source()
{
	
}

// public functions

sourceEmission Source::emitParticle(int sourceType)
{
  sourceEmission emission;
  emission.nParticlesEmitted = 0;
  
  switch(sourceType) {
    
  case 22 : {
    // Na22 Source
    emission.nParticlesEmitted = 3;
    emission.particlesEmitted = new Particle * [emission.nParticlesEmitted];
    emission.particlesEmitted[0] = new Particle(rng_,1275,uniform_law()*2*M_PI,position_);
    double theta = uniform_law()*M_PI;
    emission.particlesEmitted[1] = new Particle(rng_,511,theta,position_);
    emission.particlesEmitted[2] = new Particle(rng_,511,theta+M_PI,position_);
    break;
  }
    
  default : {
    // SIMPLE SOURCE (1 GAMMA - 1 ENERGY)
    double energy = energy_;
    emission.nParticlesEmitted = 1;
    emission.particlesEmitted = new Particle * [emission.nParticlesEmitted];
    emission.particlesEmitted[0] = new Particle(rng_,energy,uniform_law()*2*M_PI,position_);
    break;
  }
  }
  return emission;
}