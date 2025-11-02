#include <stdio.h>


int main(int argc, char* argv[]){
  if (argc <= 1) return 1;
  
  FILE* f = fopen(argv[1], "r+");
  
  fseek(f, 0, SEEK_END);
  long s = ftell(f);

  if (s<2) return 0;

  fseek(f, 0, SEEK_SET);
  char c = getc(f);

  fseek(f, 1, SEEK_SET);
  putc(c, f);

  fclose(f);
  
  return 0;
}

