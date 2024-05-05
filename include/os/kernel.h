#include <os/types.h>

#define define_buffer(t) struct __buffer_##t { \
    t *ptr; \
    size_t cap; \
    size_t len; \
};

#define buffer(t) struct __buffer_##t 
#define buffer_push(t, buf, x) do { \
    struct __buffer_##t *self = (buf); \
    if (self->len == self->cap) { \
        assert(false && "cannot expand buffer"); \
    } \
    self->ptr[self->len++] = (x); \
} while (0)

define_buffer(char)

void kern32(void);
