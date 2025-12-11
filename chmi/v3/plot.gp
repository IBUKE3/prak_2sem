set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'result.png'

set xlabel "X"
set ylabel "Y"
set title "Сравнение интерполяции и исходных данных"
set grid
set key top left

# interp.txt - линия интерполяции, data.txt - точки данных
plot "9interp1011.txt" with lines linewidth 2 title "Интерполяция", \
     "9data.txt" with points pointtype 7 pointsize 1.5 title "Исходные данные"

set output

