set terminal eps enhanced
set output "vector2.ps"

set xrange [-1000:1000]
set yrange [-1000:1000]

plot "data2vec.dat" using 1:2:3:4 with vectors filled head lw 1
