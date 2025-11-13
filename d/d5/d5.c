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
  //printf("length = %lu\n", length(lst));
  while (lst) {
    printf("%d ", lst -> data);
    lst = lst -> next;
  }
  printf("\n");
}


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


void duplicator(List* plst){
  List lst = *plst;
  List lstsaver = lst;
  List templ = NULL;
  while (lst) {
    if (lst -> data > MINNUM) {
      append(&templ, create(lst->data));
    }
    lst = lst -> next; 
  }
  if (length(templ)>0){
    reverse(&templ);
    *plst = templ;
    while(templ && templ -> next) {
      templ = templ -> next;
    }
    templ -> next = lstsaver;
  }
}


int main(void){
  List m = input();
  duplicator(&m);
  print(m);
  release(&m);
  return 0;
}
