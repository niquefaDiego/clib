#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ds/DoublyLinkedList.h"

typedef struct DoublyLinkedListNode node_t;

node_t* newWrappedInt(int x) {
  node_t *node = DoublyLinkedListNode_New(sizeof(int));
  memcpy(node->data, (char*) &x, sizeof(int));
  return node;
}

int unwrapInt(node_t* node) {
  return *((int*)node->data);
}

int expectedList[] = { 0, 3, 5, 10, 20, 25 };
int expectedListLength = 6;

int main()
{
  node_t *head = 0, *tail = 0;

  DoublyLinkedList_RPush(&head, &tail, newWrappedInt(10));
  DoublyLinkedList_RPush(&head, &tail, newWrappedInt(20));
  DoublyLinkedList_LPush(&head, &tail, newWrappedInt(5));
  DoublyLinkedList_LPush(&head, &tail, newWrappedInt(3));
  DoublyLinkedList_LPush(&head, &tail, newWrappedInt(0));
  DoublyLinkedList_RPush(&head, &tail, newWrappedInt(25));
  
  // iterate forward
  node_t *node = head;
  int i = 0;
  while (node) {
    assert(i < expectedListLength && unwrapInt(node) == expectedList[i++]);
    node = node->next;
  }
  assert(i == expectedListLength);

  // iterate backwards and free memory
  node = tail;
  i = expectedListLength - 1;
  node_t *toFree = 0;
  while (node) {
    assert(i >= 0 && unwrapInt(node) == expectedList[i--]);
    toFree = node;
    node = node->prev;
    free(toFree);
  }
  assert(i == -1);

  return 0;
}