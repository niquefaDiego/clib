#ifndef CLIB_DS__DOUBLY_LINKED_LIST_H
#define CLIB_DS__DOUBLY_LINKED_LIST_H

struct DoublyLinkedListNode {
  struct DoublyLinkedListNode *prev;
  struct DoublyLinkedListNode *next;
  unsigned char data[];
};

struct DoublyLinkedListNode* DoublyLinkedListNode_New(size_t dataSize);

void DoublyLinkedListNode_InsertAfter(
  struct DoublyLinkedListNode **nodeRef,
  struct DoublyLinkedListNode *toInsert);

void DoublyLinkedListNode_InsertBefore(
  struct DoublyLinkedListNode **nodeRef,
  struct DoublyLinkedListNode *toInsert);

void DoublyLinkedList_LPush(
  struct DoublyLinkedListNode **headRef,
  struct DoublyLinkedListNode **tailRef,
  struct DoublyLinkedListNode *newNode);

void DoublyLinkedList_RPush(
  struct DoublyLinkedListNode **headRef,
  struct DoublyLinkedListNode **tailRef,
  struct DoublyLinkedListNode *newNode);

#endif