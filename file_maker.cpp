#include "file_maker.h"

int file_maker(int * size, double ** outtable)
{
	ofstream outfile("test.csv", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
	
	int i;
	
	if(outfile)
	{
		outfile << "il y a " << size[1] << " lignes et " << size[2] << " colonnes" << endl;
	
		for(i=0 ; i<size[1] ; i++){
			outfile << outtable[i][1] << ";" << outtable[i][2] << endl;			
		}	
		
		outfile.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	
	return 0;
}
