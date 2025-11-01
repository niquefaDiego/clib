#ifndef MYCSTD_DS__STRING_H
#define MYCSTD_DS__STRING_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef struct {
  char *str;
  size_t size;
  size_t capacity;
} String;

typedef struct {
  char *str;
  size_t size;
} StringView;

String* String_ReadToken(FILE*);
void String_Free(String*);

#ifdef __cplusplus
}
#endif
#endif // MYCSTD_DS__STRING_H