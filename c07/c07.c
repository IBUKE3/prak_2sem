#include <stdio.h>
#include <ctype.h>
#include <string.h>


enum {MAX_LEN = 80+2};


void split_fin(char* words[], char* str){
  while(*str){
    while (*str && isspace(*str)) str++; // skipiing first spaces
    *words++ = str; // pointer at the beginning of the word
    while(*str && !(isspace(*str))) str++; // skipping the word
    if (*str) { *str = 0; str++; };
  }
  *words = NULL; // for print3 - end of the array
}	


void print3(char* words[]){
  char* q = *words;
  while (q!=NULL){
    if(strlen(q)>=3){ 
      putc(*q, stdout);
      putc(*(q+1), stdout);
      putc(*(q+2), stdout);
      putc('\n', stdout); 
    }
    q=*(++words);
  }
  /*while(q!=NULL){
    printf("%s\n",q);
    q = *words++;
  }*/ // use for whole strings output
  return;
}


int main(void){
  char s[MAX_LEN];
  char* w[MAX_LEN]; // more than needed, but guarantied
  if (fgets(s, sizeof(s), stdin)==NULL) return 0;

  split_fin(w, s);
  print3(w);

  return 0;
}

