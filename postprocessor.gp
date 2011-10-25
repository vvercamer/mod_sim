#http://www.pct.espci.fr/~florent/gnu.html
# Input file contains comma-separated values fields
set datafile separator ";"

plot "test.csv" using 1:2 with lines
pause 4
