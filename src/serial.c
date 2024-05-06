#include <os/serial.h>
#include <os/x86.h>

void serial_init(struct serial_dev *out, u16 port) {
    outb(port+SRAL_INTR_ENABLE, 0x00);
    outb(port+SRAL_LCR, 0x80); // Unlock BAUD rate divisor
    outb(port+SRAL_BAUD_LO, 0x03);
    outb(port+SRAL_BAUD_HI, 0x00);

    outb(port+SRAL_LCR, 0x03); // 8 bits, no parity, one stop bit
    outb(port+SRAL_FIFOCR, 0xC7); // Enable FIFO, clear them, with 14-byte threshold

    // (no-loopback, with IRQs enabled, and OUT#1 and OUT#2 bits enabled)
    outb(port+SRAL_MCR, 0x0F);

    out->port = port;
}

void serial_send(struct serial_dev* dev, u8 byte) {
    u16 port = dev->port;
    while ((inb(port+SRAL_LSR) & 0x20) == 0) {}
    outb(port, byte); 
}

ssize_t serial_console_write(void *dev, u8 *data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        serial_send(dev, data[i]);
    }
    return len;
}
