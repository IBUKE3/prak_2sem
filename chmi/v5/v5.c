#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef long double ld;

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

void compute_range(ld (*f)(ld x), ld (*f_der)(ld x), int n, char* interf, char* funcf) {
  ld h = M_PI/(n-1);

  ld *x = malloc(n*sizeof(ld));
  ld *y = malloc(n*sizeof(ld));
  ld *y_der = malloc(n*sizeof(ld));
  ld *A = malloc(n*sizeof(ld));
  ld *D = malloc(n*sizeof(ld)); // denominators for each fracture

  ld t = 0;
  
  //FILE* out = fopen("9data.txt", "w");
  //FILE* myout = fopen("9myout.txt", "w");


  for (int i = 0; i < n; i++) {
    x[i] = t;
    y[i] = f(t);
    y_der[i] = f_der(t);
    t += h;
    //fprintf(out, "%Lf %Lf\n", x[i], y[i]);
  }

  for (int i = 0; i < n; i++) {
    A[i] = 0;
    D[i] = 1;
    for (int j = 0; j < n; j++) {
      if (j!=i) {
        A[i] += 1/(x[i]-x[j]);
	D[i] /= pow(x[i]-x[j], 2);
      }
    }
  }

  ld prod;
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

    //fprintf(myout, "%Lf %Lf\n", x[i], temp);
  }

  FILE* ifile = fopen(interf, "w");
  FILE* dfile = fopen(funcf, "w");

  h = 0;
  for (int it = 0; it < 1001; it++) {
    for (int i = 0; i < n; i++) {
      t = 0;
      for (int k = 0; k < n; k++) {
        prod = 1;
        for (int j = 0; j < n; j++) {
          if (j != k) {
            prod *= pow((h-x[j]),2);
  	  }
        }
	prod *= D[k];
        t += (y[k] + (y_der[k]-2*y[k]*A[k])*(h - x[k])) * prod;
      }
    }
    fprintf(ifile, "%Lf %Lf\n", h, t);
    fprintf(dfile, "%Lf %Lf\n", h, f(h));
    h += M_PI/1000;
  }


  free(x);
  free(y);
  free(y_der);
  free(A);
  free(D);
  //free(interp);
  //fclose(out);

}

void plot(void) {
  FILE *in = fopen("data.txt", "r");
  fclose(in);
}



int main(void) {
  compute_range(f1, f1_der, 5, "5interp.txt", "5data.txt");
  compute_range(f1, f1_der, 9, "9interp.txt", "9data.txt");
  compute_range(f1, f1_der, 17, "17interp.txt", "17data.txt");
  compute_range(f1, f1_der, 33, "33interp.txt", "33data.txt");
  return 0; 

}
