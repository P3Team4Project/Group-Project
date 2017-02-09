set view map
unset surface
set contour base
set cntrparam levels discrete -100,-75,-50,-25,-0.001,0.001,25,50,75,100
set isosam 31,31
set table 'equipotential_lines.txt'
splot "data1.dat" w l ls 1
unset table

set terminal eps enhanced
set output "countour1.ps"

plot 'equipotential_lines.txt' u 1:2 w l ls 1, 'grad1.dat' u 1:2:3:4 w vectors lw 1
