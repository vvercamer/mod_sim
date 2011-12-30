#http://www.pct.espci.fr/~florent/gnu.html
# Input file contains comma-separated values fields
set datafile separator ";"
#set logscale xy
#plot [] [:20]'proba.csv' using 1:2 title "photoelectrique" with lines, '' using 1:3 title "compton"  with lines, '' using 1:4 title "creation de paires"  with lines
plot "histo_result.csv" using 1:2 with lines
pause 4
