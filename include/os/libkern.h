#include <os/types.h>

#define MAX_CONSOLES 4

struct console_ops {
    ssize_t (*write)(void *instance, u8 *data, size_t len);
};

struct console_dev {
    void *instance;
    struct console_ops ops;
};

void console_write(struct console_dev *dev, u8 *data, size_t len);
void kputs(const char *str, size_t len);
void kputs_c(const char *str);

typedef struct core {
    struct console_dev consoles[MAX_CONSOLES];
    size_t consoles_cnt;
} core_t;

extern core_t core;

void core_init(void);
void core_add_console(struct console_dev dev);
void panic(const char *cstr);
