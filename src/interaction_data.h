#ifndef _INTERACTION_DATA_H
#define _INTERACTION_DATA_H

static const double Na_Z = 13;
static const double Na_A = 23;
static const double I_Z = 53;
static const double I_A = 127;

static const int nLines = 92;
static const int nColumns = 5;

// The initData function stores in a 3D array the interaction data for Na and I
// Use : data[a][b][c]
// a = 0 : Sodium ; a = 1 : Iodine

// b = 0 : Energy (keV) ; 
// b = 1 : Compton Cross Section (cm^2 / g) ;
// b = 2 : Photoelectric Effect Cross Section (cm^2 / g) ; 
// b = 3 : Pair Creation Cross Section (cm^2 / g)
// b = 4 : Total Cross Section (cm^2 / g)

// c : browse different energy lines (from 0 to 91 (nLines -1))
  
int initData(double *** data);
int loadData(double ** dataArray, string dataPath);

// electron shells energies (keV)
static const double I_Shells[] = {33.17, 5.188, 4.852, 4.557, 1.072, 0}; //energy (keV) K, L1, L2, L3, M1
static const double Na_Shells[] = {1.072, 0};//energy (keV) K

// Auger / Fluo probabilities

static const double I_Auger = 0.9;
static const double I_Fluo = 0.1;

static const double Na_Auger = 0.1;
static const double Na_Fluo = 0.9;

#endif
