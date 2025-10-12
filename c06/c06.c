#include <stdio.h>


enum {MAX_LEN = 80 + 2};


char* findchar(const char* str, char c){
  char* p = (char*) str;
  while (*p++!=c){
    if (*p == 0) return NULL;
  }
  return p-1;
}


int main(void){
  char s[MAX_LEN];
  if(fgets(s, sizeof(s), stdin)==NULL) return 0;
  char* q = findchar(s, 'Q');
  while (q!=NULL){
    *q = 'R';
    q = findchar(s, 'Q');
  }
  q = findchar(s, '\n');
  while(q!=NULL){
    *q = 0;
    q = findchar(s, '\n');
  }
  
  if(puts(s)<0) return -1;

  return 0;
}

