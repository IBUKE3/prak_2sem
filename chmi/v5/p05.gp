set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'result5.png'

set xlabel "X"
set ylabel "Y"
set title "Сравнение интерполяции и исходных данных"
set grid
set key top left

# interp.txt - линия интерполяции, data1011.txt - график исходных данных
plot "5interp.txt" with lines linewidth 2 title "Интерполяция", \
     "5data.txt" with lines linewidth 1.5 linecolor rgb "red" title "Исходные данные"

set output

