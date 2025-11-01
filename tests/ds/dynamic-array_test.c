#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mycstd.h>

void Test1() {
  DynamicArray* DynamicArray = DynamicArray_New(sizeof(int), 2);

  int expectedList[] = { 0, 3, 5, 10, 20, 25 };
  int expectedListLength = 6;

  DynamicArray_Push(DynamicArray,int,0);
  DynamicArray_Push(DynamicArray,int,3);
  DynamicArray_Push(DynamicArray,int,5);
  DynamicArray_Push(DynamicArray,int,10);
  DynamicArray_Push(DynamicArray,int,20);
  DynamicArray_Push(DynamicArray,int,25);
  
  assert(DynamicArray->size == expectedListLength);
  assert(DynamicArray->capacity >= DynamicArray->size);
  int* actualArray = (int*)DynamicArray->array;
  for (int i = 0; i < expectedListLength; ++i) {
    assert(actualArray[i] == expectedList[i]);
  }

  DynamicArray_Free(DynamicArray);
}


void Test2() {
  DynamicArray* DynamicArray = DynamicArray_New(sizeof(char*), 2);

  const char* expectedList[] = { "foo", "bar", "magic" };
  int expectedListLength = 3;

  DynamicArray_Push(DynamicArray,char*,"foo");
  DynamicArray_Push(DynamicArray,char*,"bar");
  DynamicArray_Push(DynamicArray,char*,"magic");
  
  assert(DynamicArray->size == expectedListLength);
  assert(DynamicArray->capacity >= DynamicArray->size);
  char** actualArray = (char**)DynamicArray->array;
  for (int i = 0; i < expectedListLength; ++i) {
    assert(strcmp(actualArray[i],expectedList[i]) == 0);
  }

  DynamicArray_Free(DynamicArray);
}

int main()
{
  Test1();
  Test2();
  return 0;
}