struct Node {
	    struct Node * next;
	        int data;
};

typedef struct Node Node;  // узел списка

typedef struct Node* List; // список = указатель на узел
		

Node* create(int n);
void append(List* pList, Node* item);
void release(List* pList);
List input(void);
size_t length(List lst);
void print(List lst);

