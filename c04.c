#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//char* fgets( char* str, int count, FILE* stream );

enum { MAXLEN = 80+2 };


char* concat(const char* s1, const char* s2){
  const char* p = s1;
  char* r = malloc(strlen(s1)+strlen(s2)+1);
  short lenr = 0;
  while ((*p!='\0')&&(*p!='\n')) {
    *r=*p;
    r++; lenr++; p++;
  }
  p = s2;
  while ((*p!='\0')&&(*p!='\n')) {
    *r=*p;
    r++; lenr++; p++;
   }
  *r='\0';
  return r-lenr;
}

int main(void){
  char s1[MAXLEN];
  char s2[MAXLEN];
  if (fgets(s1, MAXLEN, stdin)==0) return 0;
  if (fgets(s2, MAXLEN, stdin)==0) return 0;
  char* ans = concat(s1, s2);
  printf("%s\n", ans);
  free(ans);
  return 0;
}

