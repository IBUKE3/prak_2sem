#include <string.h>
#include <limits.h>


//returns -1 for wrong digit, otherwise - decimal representation
int char_to_digit(char c, int base) {
  if ((c-'0' >= 0) && (c-'0' <= base)) return c-'0';
  if ((c-'a' >= 0) && (c-'a' <= base)) return c-'a'+10;
  if ((c-'A' >= 0) && (c-'A' <= base)) return c-'A'+10;  
  return -1;
} 


int strtoint(const char str[], int base, int *res) {
  short l = strlen(str);
  long b = 1;
  int t = 0;
  long r = 0;
  if (l==0) return -1; // empty string
  for (char* p = (char*)str+l-1; p >= (char*)str; p--){
    t = char_to_digit(*p, base);
    if (t==-1) return -1; // wring diigt for this base
    r+=b*t;
    b*=base;
  }
  if (r >= INT_MAX) return -1; // overflow of int
  *res=r;
  return 1;
}
