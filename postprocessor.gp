# Input file contains comma-separated values fields

set datafile separator ";"
set xlabel "Energie (keV)"
set ylabel "Nombre d'événements"
set nokey
#set term aqua
#set logscale y
#plot "../CR-mod_sim/images/histo_result-n100M-60Co.csv" using 1:2 with lines
plot "histo_result.csv" using 1:2 with lines
