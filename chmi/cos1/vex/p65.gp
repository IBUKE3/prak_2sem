set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'result65.png'

set xlabel "X"
set ylabel "Y"
set title "Сравнение интерполяции и исходных данных"
set grid
set key top left

# interp.txt - линия интерполяции, data1011.txt - график исходных данных
plot "65interp1011.txt" with lines linewidth 2 title "Интерполяция", \
     "65data1011.txt" with lines linewidth 1.5 linecolor rgb "red" title "Исходные данные"

set output

