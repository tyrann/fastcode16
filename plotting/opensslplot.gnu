set term png
set output "openssl.png"

if (!exists("MP_LEFT"))   MP_LEFT = .1
if (!exists("MP_RIGHT"))  MP_RIGHT = .95
if (!exists("MP_BOTTOM")) MP_BOTTOM = .1
if (!exists("MP_TOP"))    MP_TOP = .9
if (!exists("MP_GAP"))    MP_GAP = 0.05

set multiplot layout 2,2 columnsfirst title "{/:Bold=15 Comparison with OpenSSL}"\


set style data histogram
set style histogram clustered gap 1
set style fill solid 0.4 border


set xlabel 'Shift'
set ylabel 'Execution time'
#set xrange [-2*pi:2*pi]
#set yrange [0:1]
set xtics font ", 6"
plot "openssl.csv" using 2:xticlabels(1) lt 1 title ""

set xlabel 'Add'
set ylabel 'Execution time'
#set xrange [-2*pi:2*pi]
#set yrange [0:1]
plot "openssl.csv" using 3:xticlabels(1) lt 2 title ""

unset ylabel
unset ytics

unset xlabel
set xlabel 'Mult'
#set xrange [-2*pi:2*pi]
#set yrange [0:1]
plot "openssl.csv" using 4:xticlabels(1) lt 3 title ""

set xlabel 'Montgomery mult'
#set xrange [-2*pi:2*pi]
#set yrange [0:1]
plot "openssl.csv" using 5:xticlabels(1) lt 4 title ""
unset multiplot