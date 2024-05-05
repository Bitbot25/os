#include <os/libkern.h>
#include <os/string.h>
#include <os/x86.h>

core_t core;

void core_init(void) {
    core.consoles_cnt = 0;
}

void core_add_console(struct console_dev dev) {
    core.consoles[core.consoles_cnt++] = dev;
}

void panic(const char *cstr) {
    kputs_c("kernel panic: ");
    kputs_c(cstr);
    x86_abort();
}

void console_write(struct console_dev *dev, u8 *data, size_t len) {
    dev->ops.write(dev->instance, data, len);
}

void kputs(const char *str, size_t len) {
    for (size_t i = 0; i < core.consoles_cnt; ++i) {
        console_write(&core.consoles[i], (u8*)str, len /* assume sizeof(char) == sizeof(u8) */);
    }
}

void kputs_c(const char *str) {
    kputs(str, strlen(str));
}
