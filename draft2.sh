#!/bin/bash

gnuplot << EOF


set view map
unset surface
set contour base
set cntrparam levels auto 20
set isosam 31,31
set table 'equipotential_lines.txt'
splot "draft3.dat" w l ls 1
unset table
unset key
#set xrange [0:50]
#set yrange [0:50]
set lmargin at screen 0;
set rmargin at screen 1;
set bmargin at screen 0.0;
set tmargin at screen 1;
unset xtics
unset ytics
unset border

set terminal pngcairo size 800,600 enhanced
set output 'contour1.png'
plot 'equipotential_lines.txt' u 1:2 w l ls 1, 'grad1.dat' u 1:2:3:4 w vectors lw 1



EOF

convert contour1.png contour1.jpg

exit 0
