#!/bin/bash

make


rm -r *.pdf

rm -r draft3.dat

touch draft3.dat

rm -r *.o

./SOR3


gnuplot << EOF

set size square

set output "SOR3.ps"
set terminal postscript color
set terminal postscript enhanced

set key opaque
set title "Solution to Laplace's Equation"


set yrange [0:30]
set xrange [0:30]
set zrange [-100:100]

set xlabel "Y"
set ylabel "X"
set zlabel "V"


set pm3d map
#set palette defined (0 "blue",1 "cyan",2 "black",3 "pink", 4 "red")
set palette defined (0 "black",1 "cyan",2 "blue")


splot "draft3.dat"  u 1:2:3 with pm3d title "Electric Potential Distribution"


EOF

ps2pdf SOR3.ps
xdg-open SOR3.pdf

exit 0
