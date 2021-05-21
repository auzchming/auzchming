#include <stdlib.h>
#include "linklist.h"

LinkedList *createLinkedList(void)
{
    LinkedList *LL = NULL;
    LL = (LinkedList *)malloc(sizeof(LinkedList));
    LL->head = NULL;
    LL->tail = NULL;
    LL->count = 0;
    return LL;
}

void insertStart(LinkedList *list, void *entry)
{

    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->next = list->head;
    newNode->next->prev = newNode;
    newNode->prev = NULL;
    list->head = newNode;
    list->count++;
}

void* removeStart(LinkedList *list)
{
    
    void* data = NULL;
    LinkedListNode* firstNode = list->head;
    if(firstNode != NULL)
    {
        data = firstNode->data;
        list->head = firstNode->next;
        list->head->prev = NULL;
        free(firstNode);
        list->count--;
    }
    return data;
}

void insertLast(LinkedList *list, void *entry)
{
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->next = NULL;
    newNode->prev = list->tail;
    newNode->prev->next = newNode;
    list->tail = newNode;
    list->count++;
}

void *removeLast(LinkedList *list)
{
    void *data = NULL;
    LinkedListNode *lastNode = list->tail;
    if(lastNode != NULL)
    {
        data = lastNode->data;
        list->tail = lastNode->prev;
        list->tail->next = NULL;
        free(lastNode);
        list->count--;
    }
    return data;
}

void printLinkedList(LinkedList* list, listFunc funcPtr)
{
    LinkedListNode *curr = list->head;
    while(curr != NULL)
    {
        (*funcPtr)(curr->data);
        curr = curr->next;
    }
}

void freeLinkedList(LinkedList* list, listFunc funcPtr)
{

    LinkedListNode *curr = list->head;
    LinkedListNode *nextCurr = NULL;
    
    while(curr != NULL)
    {
        nextCurr = curr->next;
        (*funcPtr)(curr->data);
        free(curr);
        curr = nextCurr;
    }
    free(list);
}
