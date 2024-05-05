#pragma once
#include <os/types.h>

#define str(cstr) (str_t) { .len = (sizeof(cstr) / sizeof(char)) - 1, .ptr = cstr }

typedef struct string {
    char *ptr;
    size_t len;
    size_t cap; 
} string_t;

typedef struct str {
    size_t len;
    char *ptr;
} str_t;

void string_init_buf(string_t *str, char *ptr, size_t cap);
void string_init(string_t *str);
string_t string_create_buf(char *ptr, size_t cap);
string_t string_create(void);
void string_push(string_t *str, char c);
void string_pushstr(string_t *str, str_t data); 
void string_pushcstr(string_t *str, char* data);
size_t strlen(const char* str);
