#include <stdlib.h>
#include <assert.h>
#include <ds/doubly-linked-list.h>

#define Node DoublyLinkedListNode

Node* DoublyLinkedListNode_New(size_t dataSize)
{
  assert(dataSize > 0);
  Node* newNode = (Node*) malloc(sizeof(Node) + dataSize);
  newNode->next = newNode->prev = 0;
  return newNode;
}

void DoublyLinkedListNode_InsertAfter(Node **nodeRef, Node *toInsert)
{
  Node* node = *nodeRef;
  Node *tmp = node->next; // new order is: node -> toInsert -> tmp
  node->next = toInsert;
  toInsert->prev = node;
  if (tmp) {
    tmp->prev = toInsert;
    toInsert->next = tmp;
  }
}

void DoublyLinkedListNode_InsertBefore(Node **nodeRef, Node *toInsert)
{
  Node* node = *nodeRef;
  Node *tmp = node->prev; // new order is: tmp -> toInsert -> node
  node->prev = toInsert;
  toInsert->next = node;
  if (tmp) {
    tmp->next = toInsert;
    toInsert->prev = tmp;
  }
}

void DoublyLinkedList_LPush(Node **headRef, Node **tailRef, Node *newNode) {
  if (*headRef == NULL) {
    assert(*tailRef == NULL);
    *headRef = *tailRef = newNode;
  } else {
    assert(*tailRef);
    DoublyLinkedListNode_InsertBefore(headRef, newNode);
    *headRef = newNode;
  }
}

void DoublyLinkedList_RPush(Node **headRef, Node **tailRef, Node *newNode) {
  if (*headRef == NULL) {
    assert(*tailRef == NULL);
    *headRef = *tailRef = newNode;
  } else {
    assert(*tailRef);
    DoublyLinkedListNode_InsertAfter(tailRef, newNode);
    *tailRef = newNode;
  }
}