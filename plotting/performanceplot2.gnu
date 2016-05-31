set term pdf
set output "perfplot2.pdf"

# disable legend
#unset key

# label and titles
set xlabel "Key length"
set label "Performance plot Part 2" at screen 0.038, 0.95 left font "Helvetica Bold, 14"
set label "[Ops/Cycle]" at screen 0.038, 0.86 left

# layout
set tmargin at screen 0.8
set lmargin at screen 0.1

# axis
set style line 11 lc rgb '#000000' lt 1 lw 1
set border 1 back ls 11
#set format y "%02.1f"
#set format y "%01.1f"
set xrange [*:]
set yrange [0:1.7]
#set yrange [*:]
set format x "%g bits"
set xtics nomirror out
set ytics nomirror scale 0

# grid 
set object 3 rectangle from graph 0,0 to graph 1,1 fillcolor rgb"#DDDDDD" behind fs noborder
set grid ytics lt 1 lw 1 lc rgb "#FFFFFF"

# plot data
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.5
set pointintervalbox 3
set arrow from 150,1.5 to 550,1.5 ls 7
set label 'Peak performance' at 250,1.55 right textcolor ls 7
plot "performance.csv" u 1:4 w lp pt 1 ti "Optimal1","performance.csv" u 1:5 w lp pt 1 ti "Optimal2","performance.csv" u 1:6 w lp pt 1 ti "Final"