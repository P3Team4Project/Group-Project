#!/bin/bash

gnuplot << EOF

set size square

set output "SOR3.jpg"
set terminal jpeg
#set terminal postscript enhanced

set key opaque
set title "Solution to Laplace's Equation"


set yrange [0:50]
set xrange [0:50]
set zrange [-100:100]

set xlabel "Y"
set ylabel "X"
set zlabel "V"


set pm3d map
#set palette defined (0 "blue",1 "cyan",2 "black",3 "pink", 4 "red")
set palette defined (0 "black",1 "cyan",2 "blue")


splot "draft3.dat"  u 1:2:3 with pm3d title "Electric Potential Distribution"


EOF


exit 0
