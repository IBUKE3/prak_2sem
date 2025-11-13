#include <stdio.h>


struct IntNumber {
  int type;

  union {
    char cvalue;
    int ivalue;
    long lvalue;
  };
};

typedef struct IntNumber IntNumber;


int max(int a, int b) {
  return a>=b?a:b;
}


long getvalue(IntNumber s) {
  long t;
  if (s.type==0) {t = s.cvalue;}
  else if (s.type==1) {t = s.ivalue;}
  else {t = s.lvalue;};
  return t;
}


IntNumber add(IntNumber s1, IntNumber s2){
  long t1, t2;
  
  t1 = getvalue(s1);
  t2 = getvalue(s2);

  IntNumber res = {max(s1.type, s2.type), {t1+t2} };
  if (res.type==0) res.type=1;
  return res;
}


int main(void) {
/*
  IntNumber s1 = {0, {4}};
  IntNumber s2 = {0, {5}};

  IntNumber s3 = add(s1, s2);

  printf("%d %ld\n", s3.type, getvalue(s3));
*/
  return 0;
}
