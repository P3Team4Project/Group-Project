#!/bin/bash

g++ -o SOR_2 SOR_2.cpp


rm -r draft4.dat

touch draft4.dat

#This script is for running the SOR_2 script, and plotting the data it produces


#this is simply for the z scale in gnuplot
echo "Enter your minimum potential: "
read vmin
echo "Enter your maximum potential: "
read vmax


#running the script
./SOR_2





gnuplot << EOF

set size square

set output "SOR1.png"
set terminal png
set terminal png enhanced

set key opaque
set title "Solution to Laplace's Equation"


set yrange [0:50]
set xrange [0:50]
set zrange [$vmin:$vmax]

set xlabel "Y"
set ylabel "X"
set zlabel "V"



set pm3d map
#at the moment I tend to comment out the top colour scheme when I'm plotting v=0,100 and use the second colour scheme if v=-100,100, it's a bit of a pain but this is mainly for testing stuff out 

#set palette defined (0 "blue",1 "cyan",2 "black",3 "pink", 4 "red")
set palette defined (0 "black",1 "cyan",2 "blue")


splot "draft4.dat"  u 1:2:3 with pm3d title "Electric Potential Distribution"


EOF

#ps2pdf SOR.ps
open SOR1.png

exit 0
