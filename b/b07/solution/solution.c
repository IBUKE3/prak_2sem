#include <stdio.h>
#include <stdlib.h>
#include "poliz.h"


enum { MAXLENS = 80 + 2 };


int main(void){
  char inputs[MAXLENS];

  while (fgets(inputs, MAXLENS, stdin) && *inputs && *inputs!='\n') {
  
  char* ress = toPoliz(inputs);

  printf("POLIZ = %s\n", ress);
  
  free(ress);
  }

  return 0;

}
