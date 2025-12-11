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

void compute_range(ld (*f)(ld x), ld (*f_der)(ld x), int n, char* interf, char* funcf) {
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
  FILE* dfile = fopen(funcf, "w");

  ld t1 = 0; // переменная будет хранить текущее значение x в ходе цикла
  ld max_r = 0; // максимальное отклонение на равномерной сетке из 1001 узла
  ld r;
  ld t2; // значние при текущем x
  for (int it = 0; it < 1001; it++) {
    // вычисление для каждой точки сетки значения интерполянта 
    
    for (int i = 0; i < n; i++) {
      t = 0;
      for (int k = 0; k < n; k++) {

        prod = 1;
        for (int j = 0; j < n; j++) {
          if (j != k) {
            prod *= pow((t1-x[j]),2);
  	  }
        }
	prod *= D[k];

        t += (y[k] + (y_der[k]-2*y[k]*A[k])*(t1 - x[k])) * prod;
      }
    }

    t2 = f(t1);
    r = t-t2>0 ? t-t2 : t2-t;
    if (r > max_r) {
      max_r = r;
    }

    fprintf(ifile, "%Lf %Lf\n", t1, t);
    fprintf(dfile, "%Lf %Lf\n", t1, f(t1));
    t1 += M_PI/1000;
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
  fclose(dfile);
}


int main(void) {
  printf("___________________________________________________________\n");
  printf("***********************************************************\n");
  printf("                        РАБОТА С f1\n");	
  printf("***********************************************************\n");
  printf("___________________________________________________________\n");
  compute_range(f1, f1_der, 5, "5interp.txt", "5data.txt");
  compute_range(f1, f1_der, 9, "9interp.txt", "9data.txt");
  compute_range(f1, f1_der, 17, "17interp.txt", "17data.txt");
  compute_range(f1, f2_der, 33, "33interp.txt", "33data.txt");
  printf("\n");

  printf("___________________________________________________________\n");
  printf("***********************************************************\n");
  printf("                        РАБОТА С f2\n");
  printf("***********************************************************\n");
  printf("___________________________________________________________\n");
  compute_range(f2, f2_der, 5, "25interp.txt", "25data.txt");
  compute_range(f2, f2_der, 9, "29interp.txt", "29data.txt");
  compute_range(f2, f2_der, 17, "217interp.txt", "217data.txt");
  compute_range(f2, f2_der, 33, "233interp.txt", "233data.txt");
  return 0; 

}
