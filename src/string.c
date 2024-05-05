#include <os/string.h>
#include <os/libkern.h>
#include <os/types.h>

void string_init_buf(string_t *str, char* ptr, size_t cap) {
    str->ptr = ptr;
    str->cap = cap;
    str->len = 0;
}

void string_init(string_t *str) {
    string_init_buf(str, null, 0);
}

string_t string_create_buf(char *ptr, size_t cap) {
    string_t str;
    string_init_buf(&str, ptr, cap);
    return str;
}

string_t string_create(void) {
    return string_create_buf(null, 0);
}

void string_push(string_t *str, char c) {
    if (str->len == str->cap) {
        panic("cannot reallocate");
    }
    str->ptr[str->len++] = c;
}

void string_pushstr(string_t *str, str_t data) {
    for (size_t i = 0; i < data.len; ++i) {
        string_push(str, data.ptr[i]);
    }
}

void string_pushcstr(string_t *str, char* data) {
    string_pushstr(str, (str_t) { .ptr = data, .len = strlen(data) });
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
