#include "x86.h"
#include "vga.h"
#include "serial.h"
#include "page.h"
#include <stddef.h>
#include <stdint.h>

void kern32(void);
size_t strlen(const char* str);
