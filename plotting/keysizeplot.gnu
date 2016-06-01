set term pdf
set output "keysize.pdf"

# disable legend
#unset key

# label and titles
set xlabel "Key length"
set label "Speedup plot with varied private key form, compared to OpenSSL" at screen 0.038, 0.98 left font "Helvetica Bold, 14"
set label "(u=1000000..., v=1000000...   ||   u=1010101..., v=1010101...  ||  u=1111111..., v=1111111...)" at screen 0.038, 0.92 left font "Helvetica, 10"
set label "Speedup/OpenSSL X" at screen 0.038, 0.86 left
set key font ",10"

# layout
set tmargin at screen 0.8
set lmargin at screen 0.1

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
plot "keysize.csv" u 1:2 w lp pt 1 title "Key form 111111","keysize.csv" u 1:3 w lp pt 1 ti "Key form 101010", "keysize.csv" u 1:4 w lp pt 1 ti "Key form 100000"

#"speedup.csv" u 1:6 w lp pt 1 ti "OpenSSL"
