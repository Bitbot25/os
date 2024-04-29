#include "kernel.h"

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void kern32(void) {
    lgdt(0);

    struct serial_dev com1;
    serial_init(&com1, PORT_COM1);

    struct vga_text_dev vga;
    vga_text_init(&vga);
    vga_clear(&vga);

    const char *startup_msg = "OS powering on..";

    for (size_t i = 0; i < strlen(startup_msg); ++i) {
        serial_send(&com1, startup_msg[i]);
        vga_write(&vga, startup_msg[i]);
    }
}
