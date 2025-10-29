#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ds/ArrayList.h"

void Test1() {
  ArrayList_t* arrayList = ArrayList_New(sizeof(int), 2);

  int expectedList[] = { 0, 3, 5, 10, 20, 25 };
  int expectedListLength = 6;

  ArrayList_Push(arrayList,int,0);
  ArrayList_Push(arrayList,int,3);
  ArrayList_Push(arrayList,int,5);
  ArrayList_Push(arrayList,int,10);
  ArrayList_Push(arrayList,int,20);
  ArrayList_Push(arrayList,int,25);
  
  assert(arrayList->size == expectedListLength);
  assert(arrayList->capacity >= arrayList->size);
  int* actualArray = (int*)arrayList->array;
  for (int i = 0; i < expectedListLength; ++i) {
    assert(actualArray[i] == expectedList[i]);
  }

  ArrayList_Free(arrayList);
}


void Test2() {
  ArrayList_t* arrayList = ArrayList_New(sizeof(char*), 2);

  const char* expectedList[] = { "foo", "bar", "magic" };
  int expectedListLength = 3;

  ArrayList_Push(arrayList,char*,"foo");
  ArrayList_Push(arrayList,char*,"bar");
  ArrayList_Push(arrayList,char*,"magic");
  
  assert(arrayList->size == expectedListLength);
  assert(arrayList->capacity >= arrayList->size);
  char** actualArray = (char**)arrayList->array;
  for (int i = 0; i < expectedListLength; ++i) {
    assert(strcmp(actualArray[i],expectedList[i]) == 0);
  }

  ArrayList_Free(arrayList);
}

int main()
{
  Test1();
  Test2();
  return 0;
}