#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef long double ld;

ld f1(ld x) {
  ld x1 = x;
  ld res = 1;
  x *= x1; //x^2
  res -= 8*x;
  x *= x1; // x^3
  res -= 8*x;
  x *= x1; // x^4
	 printf("--%Lf--", x);
  res += 16*x; 
  // res = 16x^4-8x^3-8x^2+1
  return res;
}

ld f1_der(ld x) {
  ld x_1 = x;
  ls res = -16*x;
  x *= x_1; // x^2
  res -= 24*x;
  x *=x_1; // x^3
  res += 64*x;
  // res = 64x^3 -24x^2 - 16x
  return res;
}

void compute_range(ld (*f)(ld x), ld (*f_der)(ld x), int n) {
  ld h = M_PI/(n-1);

  ld *x = malloc(n*sizeof(ld));
  ld *y = malloc(n*sizeof(ld));
  ld *A = malloc(n*sizeof(ld));

  ld t = 0;
  
  FILE* out = fopen("data.txt", "w");


  for (int i = 0; i < n; i++) {
    x[i] = t;
    y[i] = f(t);
    t += h;

    fprintf(out, "%Lf %Lf\n", x[i], y[i]);
  }

  for (int i = 0; i < n; i++) {
    A[i] = 0;
    A[i] = 0;
    for (int j = 0; j < n; j++) {
      if (j!=i) {
        A += 1/(x[i]-x[j]);
      }
    }
  }



  free(x);
  free(y);
  fclose(out);

}

void plot(void) {
  FILE *in = fopen("data.txt", "r");
  fclose(in);
}



int main(void) {
  compute_range(f1, 65);
  return 0; 

}
