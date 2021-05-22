#include <stdlib.h>
#include "linklist.h"

/*linked list obtained from workshop 6.2*/


LinkedList *createLinkedList(void) /*creates link list*/
{
    LinkedList *LL = NULL;
    LL = (LinkedList *)malloc(sizeof(LinkedList));
    LL->head = NULL;
    LL->tail = NULL;
    LL->count = 0;
    return LL;
}

void insertStart(LinkedList *list, void *entry) /*insert start link list from head*/
{
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->next = list->head;
    if ( newNode->next != NULL )
        newNode->next->prev = newNode;
    newNode->prev = NULL;
    list->head = newNode;
    if ( list->tail == NULL )
        list->tail = newNode;
    list->count++;
}

void* removeStart(LinkedList *list) /*remove start link list*/
{
 
    void* data = NULL;
    LinkedListNode* firstNode = list->head;
    if(firstNode != NULL)
    {
        data = firstNode->data;
        list->count--;

        if ( firstNode->next != NULL )
        {
            list->head = firstNode->next;
            firstNode->next->prev = NULL;
        }
        else
        {
            list->tail = NULL;
        }

        free(firstNode);
    }
    return data;
}

void insertLast(LinkedList *list, void *entry)/*insert last link list from tail*/
{
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->next = NULL;
    newNode->prev = list->tail;
    if ( newNode->prev != NULL )
        newNode->prev->next = newNode;
    if ( list->head == NULL )
        list->head = newNode;
    list->tail = newNode;
    list->count++;
}

void *removeLast(LinkedList *list) /*remove last link list from tail*/
{
    void *data = NULL;
    LinkedListNode *lastNode = list->tail;
    if(lastNode != NULL)
    {
        data = lastNode->data;
        list->count--;

        if ( lastNode->prev != NULL )
        {
            list->tail = lastNode->prev;
            lastNode->prev->next = NULL;
        }
        else
        {
            list->head = NULL;
        }

        free(lastNode);
    }
    return data;
}

void printLinkedList(LinkedList* list, listFunc funcPtr) /*helps print link list*/
{
    LinkedListNode *curr = list->head;
    while(curr != NULL)
    {
        (*funcPtr)(curr->data);
        curr = curr->next;
    }
}

void freeLinkedList(LinkedList* list, listFunc funcPtr) /*free link list memory*/
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
