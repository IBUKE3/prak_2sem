set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'resulttrap25_true.png'

set xlabel "X"
set ylabel "Y"
set title "Сравнение численного и точного решений"
set grid
set key top left

# interp.txt - линия интерполяции, data1011.txt - график исходных данных
plot "trap_lambda_-25_h_0.0063.txt" using 1:2 with lines linewidth 2 linecolor rgb "red" title "Численное", \
     "trap_lambda_-25_h_0.0063.txt" using 1:3 with lines linewidth 1 linecolor rgb "blue" title "Точное"

set output

