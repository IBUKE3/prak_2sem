#include <stdio.h>


int main(void){
  FILE* f = fopen("doubles.bin", "w");
  double x;
  while(scanf("%lf", &x)==1) {
    fwrite(&x, sizeof(double), 1, f);
  }
  fclose(f);
  return 0;
}
