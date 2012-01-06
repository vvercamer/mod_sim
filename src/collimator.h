#ifndef _COLLIMATOR_H_INCLUDED
#define _COLLIMATOR_H_INCLUDED

#include <iostream>
using namespace std;

typedef struct
{
	double position [2];
	double diameter;
	double width;
} collimatorParameters;

class Collimator {
private :
	double position_[2];
	double diameter_;
	
public :
	Collimator(collimatorParameters parameters);
	~Collimator();
};

#endif