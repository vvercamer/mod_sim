#include "file_maker.h"

int file_maker(double *x, double *y, int n)
{
	ofstream outfile("test.csv", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
	
	int i;
	
	if(outfile)
	{
		outfile << "il y a " << n << " lignes" << endl;
	
		for(i=0 ; i<n ; i++){
			outfile << x[i] << ";" << y[i] << endl;			
		}	
		
		outfile.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	
	return 0;
}
