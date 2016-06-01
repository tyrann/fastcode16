set term pdf
set output "ecdh.pdf"

# disable legend
unset key

# label and titles
set xlabel "Key length"
set label "ECDH execution cycles comparison" at screen 0.038, 0.95 left font "Helvetica Bold, 14"
set label "[Cycles]" at screen 0.038, 0.86 left

set label "Final" at screen 0.5, 0.45 left textcolor rgb '#0060AD'
set label "OpenSSL" at screen 0.5, 0.225 left textcolor rgb '#990600'

# layout
set tmargin at screen 0.8
set lmargin at screen 0.12
set rmargin at screen 0.9

# axis
set style line 11 lc rgb '#000000' lt 1 lw 1
set border 1 back ls 11
#set format y "%02.1f"
#set format y "%01.1f"
set xrange [*:]
#set yrange [0:0.5]
set yrange [*:]
set format x "%g bits"
set xtics nomirror out
set ytics nomirror scale 0

# grid 
set object 3 rectangle from graph 0,0 to graph 1,1 fillcolor rgb"#DDDDDD" behind fs noborder
set grid ytics lt 1 lw 1 lc rgb "#FFFFFF"

# plot data
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.5
set pointintervalbox 3

set style line 2 lt 2 lc rgb '#0060AD' lw 1
set style line 3 lt 2 lc rgb '#990600' lw 1

plot "ecdh.csv" u 1:2 w lp pt 1 lc rgb '#0060AD' title "Final" , "ecdh.csv" u 1:3 w lp pt 1 lc rgb '#990600' title "OpenSSL"
