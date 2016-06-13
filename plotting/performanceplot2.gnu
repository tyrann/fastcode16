set term pdf
set output "perfplot2.pdf"

# disable legend
unset key

# label and titles
set xlabel "Key length [bits]" font "Helvetica, 18"
set label "Performance plot Part 2" at screen 0.038, 0.95 left font "Helvetica Bold, 20"
set label "[Ops/Cycle]" at screen 0.038, 0.86 left font "Helvetica, 18"

set label "Final" at screen 0.4, 0.55 left textcolor rgb '#990600' font "Helvetica, 18"
set label "Jacobian coordinates" at screen 0.4, 0.43 left textcolor rgb '#0060AD' font "Helvetica, 18"

# layout
set tmargin at screen 0.8
set lmargin at screen 0.1
set rmargin at screen 0.93
set bmargin at screen 0.18

# axis
set style line 11 lc rgb '#000000' lt 1 lw 1
set border 1 back ls 11
set format y "%02.1f"
#set format y "%01.1f"
set xrange [*:]
set yrange [0:1.8]
#set yrange [*:]
set xtics (192, 224, 256, 384, 521) nomirror out font "Helvetica, 18"
set ytics (0, 0.5, 1, 1.5) nomirror scale 0  font "Helvetica, 18"

# grid 
set object 3 rectangle from graph 0,0 to graph 1,1 fillcolor rgb"#DDDDDD" behind fs noborder
set grid ytics lt 1 lw 1 lc rgb "#FFFFFF"

# plot data
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.5
set pointintervalbox 3
set arrow from 192,1.5 to 521,1.5 ls 7 nohead
set label 'Peak performance' at 305,1.6 right textcolor ls 7 font "Helvetica, 18"
plot "performance.csv" u 1:6 w lp pt 1 lc rgb '#990600' title "Final", "performance.csv" u 1:5 w lp pt 1 lc rgb '#0060AD' title "Jacobian coordinates"
