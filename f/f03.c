#include <stdio.h>


int main(int argc, char* argv[]) {
  if (argc <= 1) return 1;

  FILE* f = fopen(argv[1], "r+");

  fseek(f, 0, SEEK_END);
  long s = ftell(f);

  if (s != 0) {
    double x, max;
    long maxpos, pos;
    
    fseek(f, 0, SEEK_SET);
    if(fread(&max, sizeof(double), 1, f)!=1) return 0;
    maxpos = 0;
    pos = 0;

    while(fread(&x, sizeof(double), 1, f)==1) {
      pos++;
      if (x>max) { max = x; maxpos = pos; };
    } // now max is maximum number

    fseek(f, (maxpos + 1)*sizeof(double), SEEK_SET); // next elem after maximum
    
    double y;
    x = max;
    while(fread(&y, sizeof(double), 1, f)==1) {
      fseek(f, -sizeof(double), SEEK_CUR);
      fwrite(&x, sizeof(double), 1, f);
      x = y;
    }
    fwrite(&x, sizeof(double), 1, f);
    printf("max = %.1lf\n", max);
  }

  fclose(f);

  return 0;
}

