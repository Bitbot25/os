#include "serial.h"
#include "x86.h"

void serial_init(struct serial_dev *out, uint16_t port) {
    outb(port+SRAL_INTR_ENABLE, 0x00);
    outb(port+SRAL_LCR, 0x80); // Unlock BAUD rate divisor
    outb(port+SRAL_BAUD0, 0x03);
    outb(port+SRAL_BAUD1, 0x00);

    outb(port+SRAL_LCR, 0x03); // 8 bits, no parity, one stop bit
    outb(port+SRAL_FIFOCR, 0xC7); // Enable FIFO, clear them, with 14-byte threshold

    // (no-loopback, with IRQs enabled, and OUT#1 and OUT#2 bits enabled)
    outb(port+SRAL_MCR, 0x0F);

    out->port = port;
}

void serial_send(struct serial_dev* dev, uint8_t byte) {
    uint16_t port = dev->port;
    while ((inb(port+SRAL_LSR) & 0x20) == 0) {}
    outb(port, byte); 
}
