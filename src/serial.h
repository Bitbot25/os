#include <stdint.h>

#define PORT_COM1 0x3f8
#define SRAL_LSR 5 // Line Status Register
#define SRAL_LCR 3 // Line Control Register
#define SRAL_DR 0  // Data Register
#define SRAL_FIFOCR 2 // FIFO Control Register
#define SRAL_MCR 4 // Modem Control Register
#define SRAL_INTR_ENABLE 1

#define SRAL_BAUD0 SRAL_DR
#define SRAL_BAUD1 SRAL_INTR_ENABLE

struct serial_dev {
    uint16_t port;
};

void serial_send(struct serial_dev *dev, uint8_t byte);
void serial_init(struct serial_dev *out, uint16_t port);
