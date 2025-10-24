#include <stdio.h>
#include <stdlib.h>


struct Node {   // узел списка
  struct Node * next;
  struct Node * prev;
  int data;
};

struct List {   // список = структура
  struct Node * first;
  struct Node * last;
  size_t len;
};

typedef struct List List;
typedef struct Node Node;


Node* create(int n) {
  Node* r = malloc(sizeof(Node));
  r -> data = n;
  r -> prev = NULL;
  r -> next = NULL;
  return r;
}


void append(List* list, Node* item) {
  if ((list -> first) == NULL) {
    list -> first = item;
    list -> last = item;
    list -> len = 1;
  } else {
    (list -> last) -> next = item;
    item -> prev = list -> last;
    (list -> len)++;
    list -> last = item;
  }
}


void input (List* list) {
  int x;
  while(scanf("%d", &x) == 1) {
    append(list, create(x));
  }
}


void rprint(const List* list) {
  Node* elem = list -> last;
  while (elem) {
    printf("%d ", elem -> data);
    elem = elem -> prev;
  }
  printf("\n");
}


void release(List* list) {
  if (list) {
    Node* elem = list -> first;
    while (elem) {
      Node* t = elem -> next;
      free(elem);
      elem = t;
    }
    list -> first = NULL;
    list -> last = NULL;
    list -> len = 0;
  }
}


int main(void) {
  List l = {NULL, NULL, 0};

  input(&l);

  rprint(&l);

  release(&l);
  return 0;
}


