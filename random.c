#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "random.h"

double unifdist ()
{
	float x=0.;	

	srand(time(NULL)) ;

//	printf("%d",MAX_RAND);
	x = rand();

	return x;
}
	
