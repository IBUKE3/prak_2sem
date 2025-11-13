#include <stdio.h>
#include <string.h>


void printArgs(char* words[]){
  char* q = *(++words);
  while(q!=NULL){
    printf("%s\n",q);
    q = *(++words);
  } // use for whole strings output
  return;
}


void printArgsWithEnd(char* words[]){
  char* q = *(++words);
  while(q!=NULL){
    char* s = strstr(q, "end");
    if (s) {s = strstr(s+3, "end");};
    if (s) {printf("%s\n", s+3); };
    q = *(++words);
  } 
}


int main(int argc, char *argv[]){
  printArgs(argv);
  printArgsWithEnd(argv);
  return 0;
}

