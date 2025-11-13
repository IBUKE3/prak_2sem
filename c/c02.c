#include <stdio.h>


char* fgets( char* str, int count, FILE* stream );
enum { MAX_LEN = 80 };


int my_strlen(const char* str){
  char* p = (char *) str;
  while ((*p != '\0') && (*p != '\n')) p++;
  return p-str;
}


int main(void){
  char s[MAX_LEN+1]; // for '/0' at the end
  if (fgets(s, MAX_LEN+1, stdin) == NULL) {
    printf("EMPTY INPUT\n"); 
    return 0;
  }
  printf("%d\n", my_strlen(s));
  return 0;
}

