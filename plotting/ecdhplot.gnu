set term pdf
set output "ecdh.pdf"

# disable legend
unset key

# label and titles
set xlabel "Key length [bits]" font "Helvetica, 18"
#set label "ECDH execution cycles comparison" at screen 0.038, 0.95 left font "Helvetica Bold, 14"
set label "[Cycles]" at screen 0.038, 0.975 left font "Helvetica, 18"

set label "Final" at screen 0.5, 0.5 left textcolor rgb '#0060AD' font "Helvetica, 18"
set label "OpenSSL" at screen 0.5, 0.25 left textcolor rgb '#990600' font "Helvetica, 18"

# layout
set tmargin at screen 0.9
set lmargin at screen 0.14
set rmargin at screen 0.95
set bmargin at screen 0.18

# axis
set style line 11 lc rgb '#000000' lt 1 lw 1
set border 1 back ls 11
set xrange [*:]
#set yrange [0:0.5]
set yrange [*:]
set xtics (192, 224, 256, 384, 521) nomirror out font "Helvetica, 18"
set ytics nomirror scale 0 font "Helvetica, 18"


# grid 
set object 3 rectangle from graph 0,0 to graph 1,1 fillcolor rgb"#DDDDDD" behind fs noborder
set grid ytics lt 1 lw 1 lc rgb "#FFFFFF"

# plot data
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.5
set pointintervalbox 3

set style line 2 lt 2 lc rgb '#0060AD' lw 1
set style line 3 lt 2 lc rgb '#990600' lw 1

plot "ecdh.csv" u 1:2 w lp pt 1 lc rgb '#0060AD' title "Final" , "ecdh.csv" u 1:3 w lp pt 1 lc rgb '#990600' title "OpenSSL"
