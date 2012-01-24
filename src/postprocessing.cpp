/***************************
 * DATA PROCESSING PROGRAM 
 * by ANTOINE GAUME
 ***************************/

/* System Headers */
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

/* System Config */
using namespace std;

/* Project Headers */

/* ROOT Headers */
#include "TROOT.h"
#include "TRint.h"
#include "TBenchmark.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TPaveLabel.h"
#include "TH1.h"
#include "TF1.h"

// Quadratic background function
Double_t background(Double_t *x, Double_t *par) {
   return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

// Lorenzian Peak function
Double_t gaussianPeak(Double_t *x, Double_t *par) {
  return (par[0]*exp(-1.*(par[1]-x[0])*(par[1]-x[0])/(2*par[2]*par[2])));
}

// Sum of background and peak function
Double_t fitFunction51(Double_t *x, Double_t *par) {
  return background(x,par) 
    + gaussianPeak(x,&par[3]);
}


/* Main Program */
int main(int argc, char * argv[])
{ 
	if (argc == 3) {
	}
	else{
		cerr << "-- ERROR -- Proper use is ./simulation <filename> <maxEnergy> " << endl;
		exit(EXIT_FAILURE);
	}
	
	string s = argv[1];
	char *a=new char[s.size()+1];
	a[s.size()]=0;
	memcpy(a,s.c_str(),s.size());
	
	double maxEnergy = atof(argv[2]);
	
	// Welcome message
	cerr << "\n== DATA POST-PROCESSING - CMI 2011-2012 ==\n" << endl;
	
	// Display configuration of the data processing
	cerr << "No configuration yet" << endl;
	
	// Declaring ROOT variables
	TCanvas *canvas;
	TApplication *theApp;
	TH1 *histo;
	
	
	theApp=new TApplication("App", &argc, argv);
	
	canvas = new TCanvas("c", "MIP simulation projet", 400, 400);
	canvas->cd();
	canvas->Update();
	
	histo  = new TH1F("histo","Distribution de la charge", 500, 0.1, maxEnergy);
	
	cerr<< a <<endl;

	
	ifstream file(a,ios::in);
	if(file){
		double output;
		while(!file.eof()){
			file >> output;
			histo->Fill(output,1.);
		}
		file.close();
	}  
	
	cerr<<"histo filled"<<endl;

	
	/*  int i=0;
	for(i=0;i<10000;i++)
	histo->Fill(10,1.);
	*/
	
	TF1 *fitFcn = new TF1("fitFcn",fitFunction51,0.,100.,6);
	fitFcn->SetNpx(500);
	fitFcn->SetLineWidth(1);
	fitFcn->SetLineColor(kMagenta);
	fitFcn->SetParameters(50,1.,2.,500,49,1.);
	histo->Fit("fitFcn","R");
	
	histo->Draw("E");
	
	theApp->Run();
	
	
	// Cleaning
	
	
	return 0;
}
 
