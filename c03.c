#include <stdio.h>

char* fgets( char* str, int count, FILE* stream );


enum {MAXLEN_1 = 80 + 1, MAXLEN_2 = 20 + 1}; 


int strfind(const char* str, const char *symbols){
  const char* p = str;
  for (const char* q = symbols; (*q != '\n') && (*q != '\0'); q++){
    p = str; // for each cycle
    while ((*p!='\0')&&(*p!=*q)) p++;
    if (*p==*q) return p-str; // index of found element, else - there is no q-element -> next q
  }
  return -1; // didn't return before
}


int main(void){
  char s1[MAXLEN_1], s2[MAXLEN_2];
  if (fgets(s1, MAXLEN_1, stdin)==0) return 0; // unused result of function
  if (fgets(s2, MAXLEN_2, stdin)==0) return 0;
  printf("%d\n", strfind(s1, s2));
  return 0;
}

