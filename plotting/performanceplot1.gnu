set term pdf
set output "perfplot1.pdf"

# disable legend
unset key

# label and titles
set xlabel "Key length [bits]" font "Helvetica, 18"
#set label "Performance plot Part 1" at screen 0.038, 0.95 left font "Helvetica Bold, 20"
set label "[Ops/Cycle]" at screen 0.02, 0.975 left font "Helvetica, 18"

set label "Memory optimization" at screen 0.5, 0.62 left textcolor rgb '#AA6000' font "Helvetica, 18"
set label "Baseline" at screen 0.5, 0.37 left textcolor rgb '#4035AD' font "Helvetica, 18"

# layout
set tmargin at screen 0.9
set lmargin at screen 0.075
set rmargin at screen 0.95
set bmargin at screen 0.18

# axis
set style line 11 lc rgb '#000000' lt 1 lw 1
set border 1 back ls 11
set format y "%02.1f"
set ytics add ('0' 0)
#set format y "%01.1f"
#set xrange [*:]

unset bars
max = 1e6
set xrange [*:]
set yrange [0:2]
#set yrange [*:]
set xtics (192, 224, 256, 384, 521) nomirror out font "Helvetica, 18"
set ytics nomirror scale 0 font "Helvetica, 18"

# grid 
set object 3 rectangle from graph 0,0 to graph 1,1 fillcolor rgb"#DDDDDD" behind fs noborder
set grid ytics lt 1 lw 1 lc rgb "#FFFFFF"

# plot data
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.5
set pointintervalbox 3
plot "performance.csv" u 1:3 w lp pt 1  lc rgb '#AA6000' title "Memory optimization", "performance.csv" u 1:2 w lp pt 1 lc rgb '#4035AD' title "Baseline"
