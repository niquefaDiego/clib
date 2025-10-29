#include "array/Sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define swap(x,y) { tmpForSwap=x; x=y; y=tmpForSwap;}
#define lt(a,b) ((a)<(b))
typedef int T;

void MergeSort(T* a, size_t n, T* tmpArray)
{
  static size_t i, j, k;
  static T tmpForSwap;
  if (n <= 1) {
    for (i = 0; i+1 < n; i++)
      for (j = i+1; j < n; j++)
        if (lt(a[j],a[i]))
          swap(a[j], a[i]);
    return;
  }
  size_t half = n/2;
  MergeSort(a, half, tmpArray);
  MergeSort(a+half, n-half, tmpArray);
  i = 0, k = 0, j = half;
  while (i < half && j < n) {
    if (lt(a[j],a[i])) tmpArray[k++] = a[j++];
    else tmpArray[k++] = a[i++];
  }
  while (i < half) tmpArray[k++] = a[i++];
  while (j < n) tmpArray[k++] = a[j++];
  memcpy(a, tmpArray, sizeof(T)*n);
}

void Int_MergeSort(int *a, size_t n) {
  int* tempArray = malloc(sizeof(int)*n);
  MergeSort(a, n, tempArray);
  free(tempArray);
}
