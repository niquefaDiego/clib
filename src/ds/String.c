#include <ds/String.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String* String_ReadToken(FILE* stream) {
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
  String* ret = malloc(sizeof(String));
  s[ret->size = i++] = '\0';
  ret->str = s;
  ret->capacity = capacity;
  return  ret;
}

void String_Free(String* string) {
  if (string) {
    free(string->str);
    free(string);
  }
}
