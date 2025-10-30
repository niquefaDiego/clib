#ifndef CLIB_DS__DOUBLY_LINKED_LIST_H
#define CLIB_DS__DOUBLY_LINKED_LIST_H
#ifdef __cplusplus
extern "C" {
#endif

struct _DoublyLinkedListNodeStruct {
  struct _DoublyLinkedListNodeStruct *prev;
  struct _DoublyLinkedListNodeStruct *next;
  unsigned char data[];
} ;

typedef struct _DoublyLinkedListNodeStruct DoublyLinkedListNode;

DoublyLinkedListNode* DoublyLinkedListNode_New(size_t dataSize);

void DoublyLinkedListNode_InsertAfter(
  DoublyLinkedListNode **nodeRef,
  DoublyLinkedListNode *toInsert);

void DoublyLinkedListNode_InsertBefore(
  DoublyLinkedListNode **nodeRef,
  DoublyLinkedListNode *toInsert);

void DoublyLinkedList_LPush(
  DoublyLinkedListNode **headRef,
  DoublyLinkedListNode **tailRef,
  DoublyLinkedListNode *newNode);

void DoublyLinkedList_RPush(
  DoublyLinkedListNode **headRef,
  DoublyLinkedListNode **tailRef,
  DoublyLinkedListNode *newNode);

#ifdef __cplusplus
}
#endif
#endif // CLIB_DS__DOUBLY_LINKED_LIST_H