#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  uint8_t *value;
  size_t length;
  size_t capacity;
} String;

String *string_from(const char init_string[]) {
  size_t init_len = strlen(init_string);

  String *string = malloc(sizeof(String));
  char *value = malloc(init_len);

  if (string == NULL || value == NULL) {
    free(string);
    free(value);
    return NULL;
  }

  string->value = (uint8_t *)value;
  string->length = init_len;
  string->capacity = init_len;

  memcpy(string->value, init_string, init_len);

  return string;
}

void print_string(const String *string) {
  for (size_t i = 0; i < string->length; i++) {
    printf("%c", string->value[i]);
  };
}

void string_free(String *string) {
  if (string != NULL) {
    if (string->value != NULL) {
      free(string->value);
    }
    free(string);
  }
}
