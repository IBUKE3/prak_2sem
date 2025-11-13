#include <stdio.h>
#include <stdlib.h>
#include "poliz.h"


enum { MAXLENS = 80 + 2 };


int main(void){
  char inputs[MAXLENS];
  
  if (!fgets(inputs, MAXLENS, stdin)) return 0;
  
  char* ress = toPoliz(inputs);

  printf("POLIZ = %s\n", ress);

  free(ress);
  return 0;

}
