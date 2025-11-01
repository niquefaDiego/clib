#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ds/dynamic-array.h>

#define ARRAY_LIST_GROWTH_FACTOR 2

DynamicArray* DynamicArray_New(size_t elementSize, size_t capacity)
{
  DynamicArray* list = (DynamicArray*) malloc(sizeof(DynamicArray));
  list->capacity = capacity;
  list->size = 0;
  list->array = (void*) malloc(elementSize * capacity);
  return list;
}

void DynamicArray_Free(DynamicArray* DynamicArray)
{
  if (DynamicArray) {
    free(DynamicArray->array);
    free(DynamicArray);
  }
}

void DynamicArray_EnsureCapacity(DynamicArray* list, size_t elementSize)
{
  assert(list);
  if (list->size == list->capacity) {
    list->capacity = 1 + list->capacity * ARRAY_LIST_GROWTH_FACTOR;
    void* newArray = malloc(list->capacity * elementSize);
    memcpy(newArray, list->array, elementSize * list->size);
    free(list->array);
    list->array = newArray;
  }
}
