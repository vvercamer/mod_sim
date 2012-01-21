#include "source.h"

Source::Source(gsl_rng * rng, sourceParameters parameters):
rng_(rng), energy_(parameters.energy), sourceType_(parameters.sourceType)
{
	position_[0]=parameters.position[0];
	position_[1]=parameters.position[1];
	switch(sourceType_) {
		case 0:
			if(LogLevel>1) cerr << "-- INFO -- You are using a monochromatic gamma source at " << energy_ << " keV" << endl;
			break;
		case 22: 
			if(LogLevel>1) cerr << "-- INFO -- You are using a 22Na source" << endl;
			break;
		case 60:
			if(LogLevel>1) cerr << "-- INFO -- You are using a 60Co source" << endl;
			break;
		default:
			cerr << "-- ERROR -- sourceType : " << sourceType_ << " is unknown !!!" << endl;
			exit(EXIT_FAILURE);
	}
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

		case 0: {
	  		// SIMPLE SOURCE (1 GAMMA - 1 ENERGY)
			double energy = energy_;
			emission.nParticlesEmitted = 1;
			emission.particlesEmitted = new Particle * [emission.nParticlesEmitted];
			emission.particlesEmitted[0] = new Particle(rng_,energy,uniform_law()*2*M_PI,position_);
			break;
		}
	    
		case 22: {
			// Na22 Source
			if (uniform_law() < 0.9) {
				emission.nParticlesEmitted = 3;
				emission.particlesEmitted = new Particle * [emission.nParticlesEmitted];
				emission.particlesEmitted[0] = new Particle(rng_,1275,uniform_law()*2*M_PI,position_);
				double theta = uniform_law()*M_PI;
				emission.particlesEmitted[1] = new Particle(rng_,511,theta,position_);
				emission.particlesEmitted[2] = new Particle(rng_,511,theta+M_PI,position_);
			}
			else {
				emission.nParticlesEmitted = 1;
				emission.particlesEmitted = new Particle * [emission.nParticlesEmitted];
				emission.particlesEmitted[0] = new Particle(rng_,1275,uniform_law()*2*M_PI,position_);
			}
			break;
		}
		
		case 60: {
			emission.nParticlesEmitted = 2;
			emission.particlesEmitted = new Particle * [emission.nParticlesEmitted];
			double theta1 = uniform_law()*2*M_PI;
			double theta2 = uniform_law()*2*M_PI;
			emission.particlesEmitted[0] = new Particle(rng_,1173.2,theta1,position_);
			emission.particlesEmitted[1] = new Particle(rng_,1332.5,theta2,position_);
			break;
		}
	
		default:
			cerr << "-- ERROR -- sourceType : "<< sourceType << " is unknown !!" << endl;
			exit(EXIT_FAILURE);
	}
	return emission;
}