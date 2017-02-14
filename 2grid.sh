#!/bin/bash


g++ -o 2grid 2grid.cpp

rm -r two_grid.dat

touch two_grid.dat

gridmax=40
d=0.1
a1=20
b1=15
r1=5
V0=100


./2grid  << EOF

$gridmax
$d
$a1
$b1
$r1
$V0


EOF


gnuplot << EOF

set size square

set output "two_grid.png"
set terminal png
set terminal png enhanced

set key opaque
set title "Solution to Laplace's Equation"


set yrange [0:40]
set xrange [0:40]
set zrange [0:100]

set xlabel "X"
set ylabel "Y"
set zlabel "V"


set pm3d map
#set palette defined (0 "blue",1 "cyan",2 "black",3 "pink", 4 "red")
set palette defined (0 "black",1 "cyan",2 "blue")


splot "two_grid.dat"  u 1:2:3 with pm3d title "Electric Potential Distribution"


EOF


open two_grid.png

exit 0
