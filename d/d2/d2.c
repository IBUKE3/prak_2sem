#include <stdio.h>
#include <stdlib.h>


struct Node {
  struct Node * next;
  int data;
};

typedef struct Node Node;  // узел списка
typedef struct Node* List; // список = указатель на узел


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
    //res += sizeof(*lst);
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

