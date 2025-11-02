
#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node * next;
    int value;
};

struct List {
    struct Node * first;
    struct Node * last;
};

struct Node* create(int value) {
    struct Node * node = malloc(sizeof(struct Node));
    *node = (struct Node) { .value = value };
    return node;
}

void append(struct List * list, struct Node * node) {
    if (list->last) {
        list->last->next = node;
        list->last = node;
    } else {
        list->first = list->last = node; 
    }
}

void print(const struct List * list)  {
    struct Node * node = list->first;
    while (node) {
        printf("%d ", node->value);
        node = node->next;
    }
    putchar('\n');
}

void release(struct List * list) {
    struct Node * node;
    while ((node = list->first)) {
        list->first = list->first->next;
        free(node);
    }
    list->first = list->last = NULL;
}

struct List merge(struct List * list1, struct List * list2) {
    // TODO
}

int main(void)
{
    struct List list1 = { };
    struct List list2 = { };
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        append(&list1, create(n));
    }
    while (scanf("%d", &n) == 1 && n != 0) {
        append(&list2, create(n));
    }

    struct List merged = merge(&list1, &list2);

    print(&merged);
    release(&merged);
    release(&list1);
    release(&list2);
}
