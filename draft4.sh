#!/bin/bash

gnuplot << EOF


set terminal pngcairo size 800,600 enhanced
set output 'SOR3.png'
#set output "SOR3.jpg"
#set terminal jpeg enhanced size 800,600
#set terminal postscript enhanced

set key opaque
#set title "Solution to Laplace's Equation"




#set yrange [0:50]
#set xrange [0:50]
set zrange [-100:100]

#set xlabel "Y"
#set ylabel "X"
#set zlabel "V"

unset key
set lmargin at screen 0;
set rmargin at screen 1;
set bmargin at screen 0;
set tmargin at screen 1;
unset xtics
unset ytics
unset border
#set colorbox noborder
set colorbox size 1,2


set pm3d map
#set palette defined (0 "blue",1 "cyan",2 "black",3 "pink", 4 "red")
set palette defined (0 "blue",1 "cyan",2 "black")


splot "draft3.dat"  u 1:2:3 with pm3d 


EOF

convert SOR3.png SOR3.jpg

exit 0
