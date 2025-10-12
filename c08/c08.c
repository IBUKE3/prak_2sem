#include <stdio.h>
#include <stdlib.h>


enum {LEFTBORDER = 5, RIGHTBORDER = 18};


// returns pointer at the beginning of the array
double* input_array(int len){
  double* p = calloc(len, sizeof(double));
    for (double* q = p; q < p + len; q++){
      if (scanf("%lf", q)!=1) return p; // unused result of scanf 
     }
     return p;
  }


void print_array(int len, double* arr){
  for (double* p = arr; p < arr + len; p++){
    printf("%.1lf ", *p);
  }
  printf("\n");
}


// returns pointer at the maximum element
double* max_el(const double * arr, int len){
  double res;
  if (len==0) return NULL;
  res = *arr;
  int ans = 0;
  for (int i = 1; i < len; i++){
    if (arr[i]>res) {
      res = arr[i];
      ans = i;
    }
  }
  return (double*)arr+ans; 
}


void swap_two_doubles(double* s1, double *s2){
  // xor realisation doesn't work because of double variables
  // realisation works for same pointers
  double t = *s1;
  *s1 = *s2;
  *s2 = t;
}


void select_sort(double* arr, int len){
  for (int i = 0; i < len - 2; i++){
    swap_two_doubles(arr+i, max_el(arr+i, len - i)); 
  }
}


int main (void) {
  int len;
  if (!scanf("%d", &len)) return 0;

  double* array = input_array(len);
 
  if (len >= RIGHTBORDER) printf("%.1lf\n", *max_el(array+LEFTBORDER-1, RIGHTBORDER - LEFTBORDER + 1));

  select_sort(array, len);

  print_array(len, array);

  free(array);

  return 0;
}

