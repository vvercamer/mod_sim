# Input file contains comma-separated values fields
set datafile separator ";"
#plot [] [:20]'proba.csv' using 1:2 title "photoelectrique" with lines, '' using 1:3 title "compton"  with lines, '' using 1:4 title "creation de paires"  with lines
set xlabel "Energie (keV)"
set ylabel "Nombre d'événements"
set nokey
set term aqua
#set logscale xy
#unset logscale; set logscale y
plot "histo_result.csv" using 1:2 with lines
#pause -1
