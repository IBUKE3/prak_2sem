#include <stdio.h>
#include <stdlib.h>


struct TNode {
  int key;
  struct TNode * left;
  struct TNode * right;
};
typedef struct TNode * Tree;
typedef struct TNode TNode;


void add(Tree* pTree, int n) {
  if (*pTree == NULL) {
    Tree temp = malloc(sizeof(TNode));
    temp -> key = n;
    temp -> left = NULL;
    temp -> right = NULL;
    *pTree = temp;
  } else {
  Tree t = *pTree;	  
  if (n < (t -> key)) { add(&(t -> left), n); } 
  else if (n > (t -> key))  { add(&(t -> right), n); }
  }
}


void release(Tree* pTree) {
  if (*pTree) {
    Tree t = *pTree;
    release(&(t -> left));
    release(&(t -> right));
    free(t);
    *pTree = NULL;
  }
}


void print(Tree tree) {
  if (tree) {
    print(tree -> left);
    printf("%d ", tree -> key);
    print(tree -> right);
  }
}


int main(int argc, char* argv[]) {
  if (argc < 2) return 0;

  char* input = argv[1];
  Tree t = NULL;

  while (*input) {
    int x = atoi(input);
    //printf("%d ", x);
    add(&t, x);
    while ((*input != ',') && (*input != '\n') && (*input)) {
      input++;
    }
    if (*input == ',') input++;
  }
  
  print(t);

  release(&t);
  return 0;
}

