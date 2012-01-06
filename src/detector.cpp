#include "detector.h"

Detector::Detector(detectorParameters parameters): diameter_(parameters.diameter), width_(parameters.width)
{
	position_[0]=parameters.position[0];
	position_[1]=parameters.position[1];
}

Detector::~Detector()
{
}

double Detector::getDensity()
{
	return density_;
}

double Detector::scintillation(double electronEnergy)
{
	return efficiency_*electronEnergy/W_;
}

double Detector::photomultiplication(double nPhotons)
{
	return nPhotons * QE_ * CE_ * G_;
}

int Detector::isIn(double x, double y)
{
	if (( x > (position_[0]-width_/2)) && ( x < (position_[0]+width_/2)) &&
		( y > (position_[1]-diameter_/2)) && ( y < (position_[1]+diameter_/2)))
		return 1;
	else
		return 0;
}