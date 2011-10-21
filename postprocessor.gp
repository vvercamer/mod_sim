# Input file contains comma-separated values fields
set datafile separator ";"

plot "test.csv" using 1:2 with lines
pause 4
