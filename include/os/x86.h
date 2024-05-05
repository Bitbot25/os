#include <os/types.h>

u8 inb(u16 port);
void outb(u16 port, u8 value);
void lgdt(void *descriptor);
void x86_reload_code_selector(u32 sel);
void x86_reload_misc_selectors(u32 sel);
void x86_abort(void);

u32 x86_cr0(void);
void x86_write_cr0(u32 cr0);
u32 x86_cr3(void);
void x86_write_cr3(u32 cr3);
u32 x86_cr4(void);
void x86_write_cr4(u32 cr4);
