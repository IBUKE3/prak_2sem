#include <stdio.h>
#include "d2.h"

int main(void){
  List mylist = input();
  print(mylist);
  release(&mylist);
  return 0;
}
