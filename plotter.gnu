set terminal png
set terminal png enhanced
set output "problem2potential.png"

reset
set key opaque
set title "Electrical potential"


set yrange [-1000:1000]
set xrange [-1000:1000]

set xlabel "Y"
set ylabel "X"
set zlabel "u"


set pm3d map
set palette defined (0 "blue",1 "cyan",2 "black",3 "pink", 4 "red")

splot "data2.dat"  u 1:2:3 with pm3d title "Temperature Difference"
unset table

