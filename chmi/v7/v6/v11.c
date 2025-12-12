#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

typedef long double ld;


int sgn(ld x) {
  // возвращает знак числа x, по сути - математическое sgn
  return x>0 ? 1 : -1;
}


ld abso(ld x) {
  // возвращает модуль числа x
  // буква o в конце для избегания конфликтов со встроенными функциями
  return x>0 ? x : -x;
}


ld f1(ld x) {
  ld res = 1;
  x *= x; // x^2
  res -= 12*x;
  x *= x; // x^4
  res += 16*x; 
  // res = 16x^4-12x^2+1
  return res;
}


ld f1_der(ld x) {
  ld x_1 = x;
  ld res = -24*x;
  x *= x_1; // x^2
  x *= x_1; // x^3
  res += 64*x;
  // res = 64x^3-24x
  return res;
}


ld f2(ld x) {
  // f2(x) = x^3 * |0.5-sin^3(2x)|
  return pow(x, 3) * abso(0.5 - pow(sin(2*x), 3));
}


ld f2_der(ld x) {
  // f2'(x) = 3x^2 * (|0.5-sin^3(2x)| - 2x*sgn(0.5-sin^3(2x))*sin^2(2x)*cos(2x))
  ld s = sin(2*x); // сохраняю в дополнительную переменную, чтобы не считать каждый раз
  return 3 * pow(x, 2) * (abso(0.5-pow(s, 3)) - 2*x*sgn(0.5-pow(s, 3))*s*s*cos(2*x));
}



void compute_range(ld (*f)(ld x), ld (*f_der)(ld x), int n, char* interf) {
  // первый аргумент - указатель на функцию
  // второй аргумент - на ее производную
  // третий - количество узлов равномерной сетки
  // четвертый - имя файла, куда будет записан результат вычисления интерполянта
  // пятый - имя файла, куда будет записан результат вычисления исходной функции

  struct timeval start_tv, end_tv;
  long long start_us, end_us;
  double elapsed_s;
  gettimeofday(&start_tv, NULL); // момент начала работы

  ld h = M_PI/(n-1); // шаг равномерной сетки
		     // рассчитываю один раз, чтобы потом не делить каждый раз на n-1

  // далее идет блок выделениия динамической памяти с целью обеспечения
  // корректной работы на различном количестве узлов
  ld *x = malloc(n*sizeof(ld)); // узлы сетки
  ld *y = malloc(n*sizeof(ld)); // значения функции в узлах
  ld *y_der = malloc(n*sizeof(ld)); // значения производной в узлах
  ld *A = malloc(n*sizeof(ld)); // см. отчет
  ld *D = malloc(n*sizeof(ld)); // знаменатели для каждой дроби, см. отчет

  ld t = 0; // вспомогательная переменная
  
  for (int i = 0; i < n; i++) {
    x[i] = t; // значение i-го узла сетки
    y[i] = f(t); // значение функции в i-ом узле
    y_der[i] = f_der(t); // значение производной в i-ом узле
    t += h; // увеличиваю вспомогательную переменную на шаг сетки
	    // считаю более рациональным, чем x[i]=i*h - меньше умножений
  }

  for (int i = 0; i < n; i++) {
    A[i] = 0; // так как сумма, то тут 0
    D[i] = 1; // так как произведение, то тут 1
    for (int j = 0; j < n; j++) {
      if (j!=i) {
        A[i] += 1/(x[i]-x[j]);
	D[i] /= pow(x[i]-x[j], 2);
      }
    }
  }

  ld prod; // вспомогательная переменная для произведения
  
  
  for (int i = 0; i < n; i++) {
    t = 0;
    for (int k = 0; k < n; k++) {
      prod = 1;
      for (int j = 0; j < n; j++) {
        if (j != k) {
          prod *= pow((x[i]-x[j]),2);
	}
      }
      prod *= D[k];
      t += (y[k] + (y_der[k]-2*y[k]*A[k])*(x[i] - x[k])) * prod;
    }
  }

  FILE* ifile = fopen(interf, "w");

  ld tx = 0; // переменная будет хранить текущее значение x в ходе цикла
  ld max_r = 0; // максимальное отклонение на равномерной сетке из 1001 узла
  ld r;
  ld ty; // значние при текущем x
  h = M_PI/1000;
  for (int it = 0; it < 1001; it++) {
    // вычисление для каждой точки сетки значения интерполянта 
    
    for (int i = 0; i < n; i++) {
      t = 0;
      for (int k = 0; k < n; k++) {

        prod = 1;
        for (int j = 0; j < n; j++) {
          if (j != k) {
            prod *= pow((tx-x[j]),2);
  	  }
        }
	prod *= D[k];

        t += (y[k] + (y_der[k]-2*y[k]*A[k])*(tx - x[k])) * prod;
      }
    }

    ty = f(tx);
    r = t-ty>0 ? t-ty : ty-t;
    if (r > max_r) {
      max_r = r;
    }

    fprintf(ifile, "%Lf %Lf\n", tx, t);
    tx += h;
  }

  gettimeofday(&end_tv, NULL); // конец вычисления
  start_us = start_tv.tv_sec * 1000000 + start_tv.tv_usec;
  end_us = end_tv.tv_sec * 1000000 + end_tv.tv_usec;

  // Вычисление прошедшего времени в миллисекундах
  elapsed_s = (double)(end_us - start_us) / 1000000.0;

  printf("___________________________________________________________\n");
  printf("Завершилось вычисление полинома Эрмита функции на %d узлах.\n", n);
  printf("              Максимальное отклонение - %Lf\n", max_r);
  printf("                   Время вычисления - %.5fс\n", elapsed_s);
  printf("___________________________________________________________\n");


  // освобождение выделенной динамической памяти
  free(x);
  free(y);
  free(y_der);
  free(A);
  free(D);

  // закрытие открытых файлов
  fclose(ifile);
}


void compute_func_1001_to_file(ld (*f)(ld x), char* funcf) {
  FILE* dfile = fopen(funcf, "w");
  ld tx = 0;
  ld h = M_PI/1000;
  for (int it = 0; it < 1001; it++) {
    fprintf(dfile, "%Lf %Lf\n", tx, f(tx));
    tx += h;
  }
  fclose(dfile);
}


void cubic_spline (ld (*f)(ld x), int m, char* splinef) {
<<<<<<< HEAD
  //int n = m; // Давайте считать n количеством отрезков для удобства (узлов m+1, но у вас m узлов всего)
=======
  int n = m; // Давайте считать n количеством отрезков для удобства (узлов m+1, но у вас m узлов всего)
>>>>>>> 70fca817511271614dabc403d16e05a11462efd6
  // В вашей логике m - это количество УЗЛОВ. Значит отрезков m-1.
  
  // !!! ВАЖНО: Исправим путаницу с N.
  // Пусть N_NODES - количество точек.
  int N_NODES = m;
  int N_SEGS = m - 1; 

  // Выделяем память. Индексы от 0 до N_NODES.
  ld *alphas = calloc(N_NODES + 1, sizeof(ld));
  ld *betas = calloc(N_NODES + 1, sizeof(ld));
  ld *c_array = calloc(N_NODES + 1, sizeof(ld));
  ld *b_array = calloc(N_NODES + 1, sizeof(ld));
  ld *d_array = calloc(N_NODES + 1, sizeof(ld));
  ld *F_array = calloc(N_NODES + 1, sizeof(ld));
  ld *x_array = calloc(N_NODES + 1, sizeof(ld));
  ld *y_array = calloc(N_NODES + 1, sizeof(ld));

  ld h = M_PI / (ld)N_SEGS; // Шаг
  ld tx = 0;

  // Заполняем x и y
  for (int i = 0; i < N_NODES; i++) {
    x_array[i] = tx;
    y_array[i] = f(tx);
    tx += h;
  }

  // --- Прямой ход прогонки ---
<<<<<<< HEAD
  //ld de = 1.0 / h; // Просто 1/h, так как в формуле F уже есть деление на h
=======
  ld de = 1.0 / h; // Просто 1/h, так как в формуле F уже есть деление на h
>>>>>>> 70fca817511271614dabc403d16e05a11462efd6
  
  // F_i = 6/h * ( (y_{i+1}-y_i)/h - (y_i - y_{i-1})/h ) / h ?? 
  // Нет, стандартная формула F_i = 6 * ( (y_{i+1}-y_i)/h - (y_i-y_{i-1})/h ) / h
  // Или проще: 6/h^2 * (y_{i-1} - 2y_i + y_{i+1})
  ld de2 = 1.0 / (h*h);

  alphas[1] = 0;
  betas[1] = 0;

  // Цикл по внутренним узлам от 1 до N_NODES-2
  for (int i = 1; i < N_NODES - 1; i++) {
    ld tf = 6 * (y_array[i-1] - 2*y_array[i] + y_array[i+1]) * de2;
    F_array[i] = tf;
    
    ld ta = 1.0 / (4.0 + alphas[i]);
    alphas[i+1] = -ta;
    betas[i+1] = ta * (tf - betas[i]);
  }

  // --- Обратный ход ---
  // Естественный сплайн: c на краях = 0
  c_array[N_NODES-1] = 0; // Последний узел
  c_array[0] = 0;         // Первый узел
  
  for (int i = N_NODES - 2; i >= 1; i--) {
    c_array[i] = alphas[i+1] * c_array[i+1] + betas[i+1];
  }

  // --- Вычисление d и b ---
  // b_array[i] и d_array[i] будут хранить коэффициенты для i-го отрезка (от x_{i-1} до x_i)
  // Индексация отрезков: 1 .. N_SEGS
  
  for (int i = 1; i <= N_SEGS; i++) {
    // d_i = (c_i - c_{i-1}) / h
    d_array[i] = (c_array[i] - c_array[i-1]) / h;
    
    // b_i = (y_i - y_{i-1})/h - h/3*c_{i-1} - h/6*c_i
    // Это формула для ПЕРВОЙ производной на ЛЕВОМ конце отрезка
    b_array[i] = (y_array[i] - y_array[i-1]) / h - (h * c_array[i-1] / 3.0) - (h * c_array[i] / 6.0);
  }

  // --- Интерполяция и вывод ---
  FILE* sfile = fopen(splinef, "w");
  ld h_new = M_PI / 1000.0;
  tx = 0;
  ld r_max = 0;

  for (int it = 0; it < 1001; it++) {
    // Определяем индекс левого узла
    int part = (int)floor(tx / h);
    
    // Защита от выхода за границу справа
    if (part >= N_SEGS) part = N_SEGS - 1;
    if (part < 0) part = 0;

    // Индекс отрезка (у нас они с 1)
    int seg_idx = part + 1;

    // Локальная координата от левого края отрезка
    ld td = tx - x_array[part];

    // S(x) = y_{i-1} + b_i*dx + c_{i-1}/2*dx^2 + d_i/6*dx^3
    ld res = y_array[part] 
           + b_array[seg_idx] * td 
           + c_array[part] * td * td / 2.0 
           + d_array[seg_idx] * td * td * td / 6.0; // !!! Деление на 6 обязательно

    ld diff = abso(res - f(tx));
    if (diff > r_max) r_max = diff;

    fprintf(sfile, "%Lf %Lf\n", tx, res);
    tx += h_new;
  }       

  printf("Максимальное отклонение: %Lf\n", r_max);
  fclose(sfile);

  free(alphas); free(betas);
  free(c_array); free(b_array); free(d_array);
  free(F_array); free(x_array); free(y_array);
}


int main(void) {
	/*
  printf("___________________________________________________________\n");
  printf("***********************************************************\n");
  printf("                        РАБОТА С f1\n");	
  printf("***********************************************************\n");
  printf("___________________________________________________________\n");
  compute_range(f1, f1_der, 5, "5interp.txt");
  compute_range(f1, f1_der, 9, "9interp.txt");
  compute_range(f1, f1_der, 17, "17interp.txt");
*/
  /*
  int t;
  if(scanf("%d", &t)==-1) return -1;
  compute_range(f1, f1_der, t, "a.txt");
  // использовать для ручного выбора количества узлов
  */
/*
  compute_range(f1, f1_der, 33, "33interp.txt");
  compute_func_1001_to_file(f1, "f1.txt");
  printf("\n");

  printf("___________________________________________________________\n");
  printf("***********************************************************\n");
  printf("                        РАБОТА С f2\n");
  printf("***********************************************************\n");
  printf("___________________________________________________________\n");
  compute_range(f2, f2_der, 5, "25interp.txt");
  compute_range(f2, f2_der, 9, "29interp.txt");
  compute_range(f2, f2_der, 17, "217interp.txt");
  compute_range(f2, f2_der, 33, "233interp.txt");
  compute_func_1001_to_file(f2, "f2.txt");
  */
  cubic_spline(f2, 17, "sf2.txt");
  return 0; 

}
