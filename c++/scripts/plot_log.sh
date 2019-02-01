#!/bin/bash

set terminal png size 1200,600
set output "../plots/search_test_log.png"
set xlabel 'Number of Keys'
set ylabel 'Time (ns)'

set logscale x 2
set xtics(0, 100, 500, 1000, 5000, 10000, 25000, 50000, 75000, 100000)

set key top center
set grid 
plot '../data/test.txt' using 1:2 w lp lw 2 lc rgb 'red' title 'Non-balanced tree',\
		'../data/test.txt' using 1:3 w lp lw 2 lc rgb 'blue' title 'Self-balanced tree',\
		'../data/test.txt' using 1:4 w lp lw 2 lc rgb 'green' title 'std::map'

replot


set output "../plots/difference.png"
set xlabel 'Number of keys'
set ylabel '% difference'
set grid
set key top center

unset logscale

set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 0.7
plot '../data/test.txt' using (($2-$3)/$3):xtic(1) tit 'unbalanced', '' u (($4-$3)/$3) tit 'std::map'