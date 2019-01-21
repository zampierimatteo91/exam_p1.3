#!/bin/bash

set terminal png size 1200,600
set output "search.png"
set xlabel 'Number of Keys'
set ylabel 'Time (us)'

set key top center

plot 'data.txt' using 1:2 w lp lw 2 lc rgb 'red' title 'Non-balanced tree',\
		'data.txt' using 1:3 w lp lw 2 lc rgb 'blue' title 'Self-balanced tree',\
		'data.txt' using 1:4 w lp lw 2 lc rgb 'green' title 'std::map'

replot

set output "figure.png"
set xlabel 'Number of keys'
set ylabel '% difference'
set grid
set key top center

set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 0.7
plot 'data.txt' using (($2-$3)/$3):xtic(1) tit 'unbalanced', '' u (($4-$3)/$3) tit 'std::map'