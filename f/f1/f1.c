#include <stdio.h>

int main (int argc, char* argv[]) {
  if (argc <= 1) return 1;
  FILE* f = fopen(argv[1], "r");
  
  char c = fgetc(f);
  
  while (c != EOF) {
    while (c != EOF && c != '\n') {
      c = fgetc(f);
    }
    if (c != EOF) c = fgetc(f);
    
    while (c != EOF && c != '\n') {
      putchar(c);
      c = fgetc(f);
    }
    if (c == '\n') putchar('\n'); 
    if (c != EOF) c = fgetc(f);
     
  }

  fclose(f);
  
  return 0;
}
