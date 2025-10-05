#include <stdio.h>
#include <stdlib.h>


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


void swap_two_doubles(double* s1, double *s2){
  // xor realisation doesn't work because of double variables
  double t = *s1;
  *s1 = *s2;
  *s2 = t;
}


int main(void){
  int len1, len2;
  
  if (scanf("%d", &len1)!=1) return 0; // have to use scanf result someway
  double* arr1 = input_array(len1);
  if (scanf("%d", &len2)!=1) return 0;
  double* arr2 = input_array(len2);
  
  // cycle from the beginnig of the first array
  for (double* p = arr1; p < arr1 + len1; p++){ 
    if (*p < 0) {
      // cycle from the end of the second array
      for (double* q = arr2 + len2 - 1; q >= arr2; q--){
        if (*q > 0) {
          swap_two_doubles(p, q);
          break;  
	}
      }
      break;
    }
  }

  print_array(len1, arr1);
  print_array(len2, arr2);
  
  free(arr1);
  free(arr2);
  
  return 0;
}

