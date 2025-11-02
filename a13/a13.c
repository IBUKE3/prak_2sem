#include <stdio.h>


int main(int argc, char* argv[]){
  unsigned long n;
  if (argc==1) return 0;
  if (sscanf(argv[1], "%lu", &n) != 1) return 0;
  printf("%lx %lx \n", n, n^((unsigned long)0xF<<(sizeof(unsigned long)*8-4)));
  return 0;
}
