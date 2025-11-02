#include <stdio.h>
#include <limits.h>


int main(void) {
  int s = 0;
  int t;
  while(scanf("%d", &t)==1) {
    // s + t > INT_MAX <=> s > INT_MAX - t
    // s + t < INT_MIN <=> s < INT_MIN - t
    if (((t>0)&&(s > INT_MAX - t)) || ((t<0)&&(s < INT_MIN - t))) {
      printf("OVERFLOW\n");
      return 0;
    }  
    s+=t;
  }
  printf("%d\n", s); 
  return 0;
}

