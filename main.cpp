#include <iostream>
#include <gsl/gsl_math.h>
using namespace std;

#include "gnuplot_i.h"

int main ()
{
	cout << "Hello World!" << endl;

	gnuplot_ctrl * h ;
    h = gnuplot_init() ;
	// gnuplot_setstyle(h, "impulses") ;
    // gnuplot_set_xlabel(h, "my X label") ;
    // gnuplot_set_xlabel(h, "my Y label") ;
	gnuplot_cmd(h, "plot x") ;
	gnuplot_close(h) ;

	cout << M_E << endl;
	return 0;
}
