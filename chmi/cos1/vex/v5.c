#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef long double ld;


int sgn(ld x) {
  return x>0? 1 : -1;
}

ld abso(ld x) {
  return x>0? x : -x;
}


ld f2(ld x) {
  // x^3 * |0.5-sin^3(x)|
  return pow(x, 3) * abso(0.5 - pow(sin(x), 3));
}

ld f2_der(ld x) {
  // 3x^2 * (|0.5-sin^3(x)| - x*sgn(0.5-sin^3(x))*sin^2(x)*cos(x))
  ld s = sin(x);
  return 3 * pow(x, 2) * (abso(0.5-pow(s, 3)) - x*sgn(0.5-pow(s, 3))*s*s*cos(x));
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
  compute_range(f2, f2_der, 5, "5interp.txt", "5data.txt");
  compute_range(f2, f2_der, 9, "9interp.txt", "9data.txt");
  compute_range(f2, f2_der, 17, "17interp.txt", "17data.txt");
  compute_range(f2, f2_der, 33, "33interp.txt", "33data.txt");
  return 0; 

}
