#ifndef LL_HGUARD
#define LL_HGUARD

/*header file that is taught in workshop 6*/
typedef struct LinkedListNode{
    void *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;

typedef struct{
    LinkedListNode *head;
    LinkedListNode *tail;
    int count;
} LinkedList;

typedef void (*listFunc)(void*data);

LinkedList *createLinkedList(void);
void insertStart(LinkedList *list, void *entry);
void *removeStart(LinkedList *list);
void insertLast(LinkedList *list, void *entry);
void *removeLast(LinkedList *list);

void printLinkedList(LinkedList* list, listFunc funcPtr);
void freeLinkedList(LinkedList* list, listFunc funcPtr);

#endif
