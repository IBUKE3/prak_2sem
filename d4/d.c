#include <stdio.h>
#include "d4.h"


void reverse(List* pList){
  List lst1 = *pList;
  if (lst1 == NULL) return;
  if (lst1 -> next == NULL) return;
  List prev = NULL;
  List lst2 = lst1 -> next;
  while (lst2){
    lst1 -> next = prev;
    prev = lst1;
    lst1 = lst2;
    lst2 = lst2 -> next;
  }
  lst1 -> next = prev;
  *pList = lst1;
}

int main(void) {
  List m = input();
  reverse(&m);
  print(m);
  release(&m);
  return 0;
}

