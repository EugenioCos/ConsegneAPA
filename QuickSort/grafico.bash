#!/bin/bash

set -e

declare -a line

output="grafico.png"

line=($(head -n 1 out_grafico.txt))
u=(${line[0]})
n=(${line[1]})
R=(${line[2]})
min=(${line[3]})
max=(${line[4]})

echo "Media empirica: ${u}, n: ${n}, r: ${R}, min: ${min}, max: ${max}"
read -p "Continuare? [y/n] " choice
if [[ $choice == [yY] ]]; then
  echo "Creo ${output}..."
else
  echo "Operazione annullata."
  exit 1
fi

#Creo grafico con i dati
gnuplot <<-eNDgNUPLOTcOMMAND
	set style data histograms
	set style histogram rowstacked
	set term png size 900, 700
	set output "${output}"
	set xlabel "n° confronti"
	set ylabel "iterazioni"
	set arrow from $u, graph 0 to $u, graph 1 nohead
	set label "û\n($u)" at $u,1800
	set grid ytics xtics
	plot "out_grafico.txt" every ::1 using 1:2 title "Iterazioni per numero di confronti\nN: $n, R: $R, min: $min, max: $max" with linespoints
	clear
eNDgNUPLOTcOMMAND


