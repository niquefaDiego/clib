#ifndef CLIB_DS__ARRAY_LIST_H
#define CLIB_DS__ARRAY_LIST_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  void *array;
  size_t size;
  size_t capacity;
}  ArrayList;

ArrayList* ArrayList_New(size_t elementSize, size_t capacity);
void ArrayList_Free(ArrayList* list);
void ArrayList_EnsureCapacity(ArrayList* list, size_t elementSize);
#define ArrayList_Push(list,dataType,value) { ArrayList_EnsureCapacity(list,sizeof(dataType)); ((dataType*)list->array)[list->size++] = value; }

#ifdef __cplusplus
}
#endif
#endif // CLIB_DS__ARRAY_LIST_H