#include "page.h"

struct gdtr gdtr;
uint64_t gdt[3] __aligned(8);

uint64_t make_sdesc(uint32_t base, uint32_t limit, uint16_t flags) {
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flags <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0
    return descriptor;
}

void gdt_init() {
    gdtr.base = (uint32_t) gdt;
    gdtr.limit = sizeof(gdt) - 1;

    gdt[0] = make_sdesc(0, 0, 0);
    gdt[1] = make_sdesc(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt[2] = make_sdesc(0, 0x000FFFFF, (GDT_DATA_PL0));

    lgdt(&gdtr);

    static_assert(SEG_SELECTOR(1) == 0x08, "");
    static_assert(SEG_SELECTOR(2) == 0x10, "");
    x86_reload_code_selector(SEG_SELECTOR(1));
    x86_reload_misc_selectors(SEG_SELECTOR(2));
}
