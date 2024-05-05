#include <os/kernel.h>
#include <os/serial.h>
#include <os/vga.h>
#include <os/page.h>
#include <os/libkern.h>

void kern32(void) {
    gdt_init();

    struct serial_dev com1;
    serial_init(&com1, PORT_COM1);

    struct vga_text_dev vga;
    vga_text_init(&vga);
    vga_clear(&vga);

    struct console_dev vga_console = {
        .instance = &vga,
        .ops = {
            .write = vga_console_write,
        }
    };

    struct console_dev serial_console = {
        .instance = &com1,
        .ops = {
            .write = serial_console_write
        }
    };

    core_init();
    core_add_console(vga_console);
    core_add_console(serial_console);

    kputs_c("OS powering on...\n");
    kputs_c("Enabling paging...\n");

    pgclear();
    pgenable();

    kputs_c("Success..?\n");
}
