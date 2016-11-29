#set grid xtics
#set grid ytics
set xlabel "Iteration(s)"
#set autoscale
set ylabel "Score"
set yrange [0:1000]
set title "Magic Square with simulated anealing"
plot "expe.dat" u 1:2 t 'choice' w lines, "expe.dat" u 1:3 t 'best' w lines
