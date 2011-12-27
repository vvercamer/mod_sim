#include "detector.h"

Detector::Detector()
{
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
