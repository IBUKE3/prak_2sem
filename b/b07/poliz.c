#include "stack.h"
#include <stdlib.h>


#include <stdio.h>


enum {MAXLEN = 80 + 2};


int is_oper(char c){
  if ((c == '+')||(c == '-')) return 1;
  if ((c == '/')||(c == '*')) return 2;
  return 0;
}



char* toPoliz(const char* expr){
  char* ans = calloc(sizeof(char), MAXLEN);
  char* p = ans;
  

  while (*expr) {
	
    if ((*expr>='0')&&(*expr<='9')) *p++ = *expr;
    
    if (*expr == '(') st_push('(');
    
    if (is_oper(*expr)) {
      while (is_oper(st_peek())>=is_oper(*expr)) {
	st_pop(p++);
      }
      st_push(*expr);
    }

    if (*expr == ')') {
      while (st_peek() && st_peek() != '(') {
        st_pop(p++);
      }
      if (st_peek()==0) {*ans = 0; return ans; }// empty string for error
      st_pop(NULL);
    }

    expr++;
  
  }

  while (!st_isempty()) st_pop(p++);

  return ans;

}

