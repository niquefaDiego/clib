#include <CLib.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

FILE* input;

void assertNextToken(const char* expectedToken) {
  String* s = String_ReadToken(input);
  assert(strcmp(expectedToken, s->str) == 0);
  assert(strlen(expectedToken) == s->size);
  assert(s->capacity >= s->size);
  assert(strlen(s->str) == s->size);
  String_Free(s);
}

int main() {
  input = fopen("tests/ds/String_Test.input.txt", "r");

  assertNextToken("this");
  assertNextToken("is");
  assertNextToken("a");
  assertNextToken("test");
  assertNextToken("case");

  fclose(input);
  return 0;
}
