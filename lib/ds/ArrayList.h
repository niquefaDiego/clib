#ifndef CLIB_DS__ARRAY_LIST_H
#define CLIB_DS__ARRAY_LIST_H

struct ArrayList {
  void *array;
  size_t size;
  size_t capacity;
};

typedef struct ArrayList ArrayList_t;

ArrayList_t* ArrayList_New(size_t elementSize, size_t capacity);
void ArrayList_EnsureCapacity(ArrayList_t* list, size_t elementSize);
#define ArrayList_Push(list,dataType,value) { ArrayList_EnsureCapacity(list,sizeof(dataType)); ((dataType*)list->array)[list->size++] = value; }

int AddThreeNumber(int a, int b, int c);

#endif