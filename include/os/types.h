#include <assert.h>
#define OSTYPE(name, src, size) typedef src name; static_assert(sizeof(src) == size, "wrong size");

#define true ((bool)1)
#define false ((bool)0)
#define null ((void*)0)

OSTYPE(u8, unsigned char, 1)
OSTYPE(u16, unsigned short, 2)
OSTYPE(u32, unsigned int, 4)
OSTYPE(u64, unsigned long long, 8)
OSTYPE(size_t, u32, 4)

OSTYPE(bool, u8, 1)

OSTYPE(s8, char, 1)
OSTYPE(s16, short, 2)
OSTYPE(s32, int, 4)
OSTYPE(s64, long long, 8)
OSTYPE(ssize_t, s32, 4)
