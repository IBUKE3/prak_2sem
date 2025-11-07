#include <stdio.h>


int main(void) {
  int res = 0;
  int c;
  while((c = fgetc(stdin)) != -1) {
    if ((c >= '0') && (c <= '9')) res += c-'0';
    if ((c >= 'a') && (c <= 'f')) res += c-'a'+10;
    if ((c >= 'A') && (c <= 'F')) res += c-'A'+10; 
  }
  printf("%d\n", res);
  return 0;
}

