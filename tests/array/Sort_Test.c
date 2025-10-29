#include "array/Sort.h"
#include <stdio.h>
#include <assert.h>

int main()
{
  int a0[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
  Int_MergeSort(a0, 8);
  for (int i = 0; i < 8; i++) assert(a0[i] == i+1);

  int a1[] = { 1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14, 17, 16, 18 };
  Int_MergeSort(a1, 19);
  for (int i = 0; i < 19; i++) assert(a1[i] == i);

  int a2[] = { 0, 1, -1, -1, 1, 0, 1, 1, 1, 0, 0, 0, -1, -1, -1 };
  Int_MergeSort(a2, 15);
  for (int i = 0; i < 12; i++) assert(a2[i] == -1 + (i/5));

  return 0;
}