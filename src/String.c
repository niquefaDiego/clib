#include <String.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char* readToken(FILE* stream) {
  int c;
  size_t capacity = 4, i = 0;
  char* s = malloc(capacity);
  while ((c = fgetc(stream)) <= 32) {
    if (c == EOF) {
      free(s);
      return NULL;
    }
  }
  s[i++] = c;
  while ((c = fgetc(stream)) > 32) { // note EOF = -1
    s[i++] = c;
    if (i == capacity)
      s = realloc(s, capacity *= 2);
  }
  s[i++] = '\0';
  return realloc(s, i+1);
}