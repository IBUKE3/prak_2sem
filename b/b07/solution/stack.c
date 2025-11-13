#include <stdio.h>

enum { STACK_CAPACITY = 8 };

static char stack[STACK_CAPACITY];
static int size = 0;

int st_isempty(void) {
  return (size==0);
}

int st_size(void) {
  return size;
}

int st_push(char c) {
  if (st_size()==STACK_CAPACITY) return -1;
  char *p = stack;
  *(p+st_size()) = c;
  size+=1;
  return 0;
}

int st_pop(char *pc) {
  if (pc==NULL) {
    size-=1;
    return 0;
  }
  if (st_isempty()) return -1;
  *pc = *(stack + st_size() - 1);
  size-=1;
  return 0;
}


char st_peek(void) {
  if (st_isempty()) return 0;
  return *(stack+st_size() - 1);
}


void st_print(void) {
  printf("size = %d : [ ", st_size());
  for (char * p = stack; p < stack + st_size(); p++) {
    printf("%c ", *p);
  }
  printf("\n");
}


