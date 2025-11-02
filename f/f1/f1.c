#include <stdio.h>

int main (int argc, char* argv[]) {
  if (argc <= 1) return 1;
  FILE* f = fopen(argv[1], "r");
  
  int c;
  char flag = 0;
  
  while ((c = fgetc(f)) != EOF) {
    if (flag) putchar(c);
    if (c == '\n') flag = !flag;
  }

  fclose(f);
  
  return 0;
}
