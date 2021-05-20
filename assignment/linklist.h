#ifndef LL_HGUARD
#define LL_HGUARD

typedef struct LinkedListNode{
	void *data;
	struct LinkedListNode *next;
} LinkedListNode;

typedef struct{
	LinkedListNode *head;
	int count;
} LinkedList;

typedef void (*listFunc)(void*data);

LinkedList *createLinkedList(void);
void insertStart(LinkedList *list, void *entry);
void *removeStart(LinekdList *list);
void insertLast(LinkedList *list, void *entry);
void *removeLast(LinkedList *list);

void printLinkedList(LinkedList* list, listFunc funcPtr);
void freeLinkedList(LinekdList* list, listFunc funcPtr);

#endif
