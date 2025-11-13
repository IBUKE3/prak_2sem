#include <stdio.h>
#include <stdlib.h>


int main(void){
  int arr_cur, arr_cap;
  int *arr;

  arr_cap = 1;
  arr_cur = 0;

  if (! (arr = (int*) malloc(arr_cap * sizeof(arr[0])))) {
    return 1;
  }

  int cur_elem;

  while (scanf("%d", &cur_elem) == 1) {
    if (arr_cur == arr_cap) {
      arr_cap *= 2;
      if (! (arr = (int*) realloc(arr, arr_cap * sizeof(arr[0])))) { return 1; };
    }
    arr[arr_cur] = cur_elem;
    arr_cur++;
  } 

  for (int* p = arr + arr_cur - 1; p >= arr; p--){
    printf("%d ", *p);
  }

  printf("\n");

  free(arr);

  return 0;
}

