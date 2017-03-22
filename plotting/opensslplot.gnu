set term pdf
set output "openssl.pdf"

if (!exists("MP_LEFT"))   MP_LEFT = .1
if (!exists("MP_RIGHT"))  MP_RIGHT = .95
if (!exists("MP_BOTTOM")) MP_BOTTOM = .1
if (!exists("MP_TOP"))    MP_TOP = .9
if (!exists("MP_GAP"))    MP_GAP = 0.05

set multiplot layout 2,2 columnsfirst

set style data histogram
set style histogram clustered gap 1
set style fill solid 0.4 border
set xtics

set xlabel 'Montgomery Mult' font "Helvetica, 18"
set ylabel 'Cycles' font "Helvetica, 18"
#set xrange [-2*pi:2*pi]
set yrange [0:250]
plot "openssl.csv" using 4:xticlabels(1) lt 3 title ""

set xlabel 'Add' font "Helvetica, 18"
set ylabel 'Cycles' font "Helvetica, 18"
#set xrange [-2*pi:2*pi]
set yrange [0:250]
plot "openssl.csv" using 2:xticlabels(1) lt 1 title ""

#set xlabel 'Mult'
#set ylabel 'Cycles'
#set xrange [-2*pi:2*pi]
#set yrange [0:7500]
#plot "openssl.csv" using 3:xticlabels(1) lt 2 title ""

set xlabel 'Shift' font "Helvetica, 18"
set ylabel 'Cycles' font "Helvetica, 18"
#set xrange [-2*pi:2*pi]
set yrange [0:50]
plot "openssl.csv" using 5:xticlabels(1) lt 4 title ""
unset multiplot
