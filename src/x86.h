#include <stdint.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);
void lgdt(void *descriptor);
void x86_reload_code_selector(uint32_t sel);
void x86_reload_misc_selectors(uint32_t sel);
