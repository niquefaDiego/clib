#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ds/ArrayList.h"

#define ARRAY_LIST_GROWTH_FACTOR 2

ArrayList_t* ArrayList_New(size_t elementSize, size_t capacity)
{
  ArrayList_t* list = (ArrayList_t*) malloc(sizeof(ArrayList_t));
  list->capacity = capacity;
  list->size = 0;
  list->array = (void*) malloc(elementSize * capacity);
  return list;
}

void ArrayList_Free(ArrayList_t* arrayList)
{
  free(arrayList->array);
  free(arrayList);
}

void ArrayList_EnsureCapacity(ArrayList_t* list, size_t elementSize)
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
