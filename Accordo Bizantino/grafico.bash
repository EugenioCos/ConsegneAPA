#!/bin/bash

set -e

declare -a line

line=($(head -n 1 out_grafico.txt))
fedeli=(${line[0]})
faulty=(${line[1]})
run=(${line[2]})

#Creo grafico con i dati
gnuplot <<-eNDgNUPLOTcOMMAND
	set style data histograms
	set style histogram rowstacked
	set term png size 900, 700
	set output "grafico.png"
	set xlabel "n° round r al raggiungimento del consenso"
	set ylabel "frequenza"
	set grid ytics xtics
	plot "out_grafico.txt" every ::1 using 1:2 title "Frequenza per r=1...10\n fedeli = $fedeli, faulty = $faulty, run = $run" with linespoints
	clear
eNDgNUPLOTcOMMAND
