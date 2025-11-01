#ifndef MYCSTD_DS__ARRAY_LIST_H
#define MYCSTD_DS__ARRAY_LIST_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  void *array;
  size_t size;
  size_t capacity;
}  DynamicArray;

DynamicArray* DynamicArray_New(size_t elementSize, size_t capacity);
void DynamicArray_Free(DynamicArray* list);
void DynamicArray_EnsureCapacity(DynamicArray* list, size_t elementSize);
#define DynamicArray_Push(list,dataType,value) { DynamicArray_EnsureCapacity(list,sizeof(dataType)); ((dataType*)list->array)[list->size++] = value; }

#ifdef __cplusplus
}
#endif
#endif // MYCSTD_DS__ARRAY_LIST_H