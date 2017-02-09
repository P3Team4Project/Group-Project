#!/bin/bash

g++ -o FMG2 FMG2.cpp

rm -r FMG2.dat

touch FMG2.dat

gridmax=40
d=0.1
a1=20
b1=20
r1=5
V0=100


./FMG2  << EOF

$gridmax
$d
$a1
$b1
$r1
$V0


EOF


gnuplot << EOF

set size square

set output "FMG2.png"
set terminal png
set terminal png enhanced

set key opaque
set title "Solution to Laplace's Equation"


set yrange [0:40]
set xrange [0:40]
set zrange [0:100]

set xlabel "Y"
set ylabel "X"
set zlabel "V"


set pm3d map
#set palette defined (0 "blue",1 "cyan",2 "black",3 "pink", 4 "red")
set palette defined (0 "black",1 "cyan",2 "blue")


splot "FMG2.dat"  u 1:2:3 with pm3d title "Potential Distribution"


EOF


open FMG2.png

exit 0
