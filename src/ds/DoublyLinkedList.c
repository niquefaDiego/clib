#include <stdlib.h>
#include <assert.h>
#include "ds/DoublyLinkedList.h"

typedef struct DoublyLinkedListNode node_t;

node_t* DoublyLinkedListNode_New(size_t dataSize)
{
  assert(dataSize > 0);
  node_t* newNode = (node_t*) malloc(sizeof(node_t) + dataSize);
  newNode->next = newNode->prev = 0;
  return newNode;
}

void DoublyLinkedListNode_InsertAfter(node_t **nodeRef, node_t *toInsert)
{
  node_t* node = *nodeRef;
  node_t *tmp = node->next; // new order is: node -> toInsert -> tmp
  node->next = toInsert;
  toInsert->prev = node;
  if (tmp) {
    tmp->prev = toInsert;
    toInsert->next = tmp;
  }
}

void DoublyLinkedListNode_InsertBefore(node_t **nodeRef, node_t *toInsert)
{
  node_t* node = *nodeRef;
  node_t *tmp = node->prev; // new order is: tmp -> toInsert -> node
  node->prev = toInsert;
  toInsert->next = node;
  if (tmp) {
    tmp->next = toInsert;
    toInsert->prev = tmp;
  }
}

void DoublyLinkedList_LPush(node_t **headRef, node_t **tailRef, node_t *newNode) {
  if (*headRef == NULL) {
    assert(*tailRef == NULL);
    *headRef = *tailRef = newNode;
  } else {
    assert(*tailRef);
    DoublyLinkedListNode_InsertBefore(headRef, newNode);
    *headRef = newNode;
  }
}

void DoublyLinkedList_RPush(node_t **headRef, node_t **tailRef, node_t *newNode) {
  if (*headRef == NULL) {
    assert(*tailRef == NULL);
    *headRef = *tailRef = newNode;
  } else {
    assert(*tailRef);
    DoublyLinkedListNode_InsertAfter(tailRef, newNode);
    *tailRef = newNode;
  }
}