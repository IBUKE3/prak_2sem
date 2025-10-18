#include <stdio.h>
#include <stdlib.h>


struct Node {
  struct Node * next;
  int data;
};

typedef struct Node Node;  // узел списка
typedef struct Node* List; // список = указатель на узел


enum {MINNUM = 50};


Node* create(int n){
  Node* res = malloc(sizeof(Node));
  res -> data = n;
  res -> next = NULL;
  return res;
}


void append(List* pList, Node* item){
  if (*pList == NULL){
    *pList = item;
  } else {
    append(&((*pList) -> next), item);
  }
}


void release(List* pList){
  List lst = *pList;
  while (lst != NULL) {
    List p = lst -> next;    
    free(lst);
    lst = p;
  }
  *pList = NULL;
}

List input(void){
  int n;
  List resL = NULL;
  while(scanf("%d", &n) == 1){
    append(&resL, create(n));
  }
  return resL;
}


size_t length(List lst){
  size_t res = 0;
  while(lst) {
    res++;
    lst = lst -> next;
  }
  return res;
}


void print(List lst){
  printf("length = %lu\n", length(lst));
  while (lst) {
    printf("%d ", lst -> data);
    lst = lst -> next;
  }
  printf("\n");
}


void swap_first_last(List* plst){
  List lst = *plst;
  List prelastel = NULL;
  List lastel = lst;
  
  if (lst == NULL) return; // empty list
  if (lst -> next == NULL) return; // one element

  if (lst -> next -> next == NULL) {
    *plst = lst -> next;
    lst -> next = NULL;
    (*plst) -> next = lst;
    return;
  }

  while (lastel -> next) {
    prelastel = lastel;
    lastel = lastel -> next;
  }

  *plst = lastel;
  lastel -> next = lst -> next;
  prelastel -> next = lst;
  lst -> next = NULL;
  
}


int main(void){
  List m = input();
  swap_first_last(&m);
  print(m);
  release(&m);
  return 0;
}
