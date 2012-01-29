#! /bin/sh
nEvent=1000000

Energy=500
# only used if sourceType=0, else : no effect.

sourceType=10
# sourceType must be 0(gamma at $Energy), 22(sodium) or 60(cobalt)

LogLevel=2
# LogLevel must be 0(ERROR), 1(WARNING) 2(INFO) or 3(DEBUG)

./simulation $nEvent $Energy $sourceType $LogLevel
coderetour=$?
if [ coderetour == 0 ]
then 
	gnuplot -persist postprocessor.gp
else
	echo "/!\ erreur dans l'exécution du programme simulation"
fi
