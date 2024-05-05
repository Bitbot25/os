#include <os/types.h>

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
    u16 port;
};

ssize_t serial_console_write(void *dev, u8 *data, size_t len);
void serial_send(struct serial_dev *dev, u8 byte);
void serial_init(struct serial_dev *out, u16 port);
