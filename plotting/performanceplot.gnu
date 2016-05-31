set term png
set output "perfplot.png"

# disable legend
#unset key

# label and titles
set xlabel "Key length"
set label "Performance plot" at screen 0.038, 0.95 left font "Helvetica Bold, 14"
set label "[Ops/Cycle]" at screen 0.038, 0.86 left

# layout
set tmargin at screen 0.8
set lmargin at screen 0.1

# axis
set style line 11 lc rgb '#000000' lt 1 lw 1
set border 1 back ls 11
set format y "%02.1f"
set xtics nomirror out
set ytics nomirror scale 0

# grid 
set object 3 rectangle from graph 0,0 to graph 1,1 fillcolor rgb"#DDDDDD" behind fs noborder
set grid ytics lt 1 lw 1 lc rgb "#FFFFFF"

# plot data
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.5
set pointintervalbox 3
plot "performance.csv" u 1:2 w lp pt 5 title "Baseline","performance.csv" u 1:3 w lp pt 7 ti "Optimal","performance.csv" u 1:4 w lp pt 9 ti "OpenSSL"