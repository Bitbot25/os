#include <os/page.h>
#include <os/types.h>
#include <os/x86.h>
#include <os/libkern.h>

struct gdtr gdtr;
u64 gdt[3] __aligned(8);

#define PAGEDIR_ENT 1024
#define PAGETBL_ENT 1024
u32 pagedir[PAGEDIR_ENT] __attribute__((aligned(4096)));

u32 pagetbl_alloc[PAGETBL_ENT][PAGEDIR_ENT];
size_t pagetbl_used;

u64 make_sdesc(u32 base, u32 limit, u16 flags) {
    u64 descriptor;
 
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

void gdt_init(void) {
    gdtr.base = (u32) gdt;
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

void pgclear(void) {
    for (size_t i = 0; i < PAGEDIR_ENT; ++i) {
        pagedir[i] = PE_PRESENT(0) | PE_RW(1) | PE_US(0);
    }
}

void ptalloc(u32 (**pagetbl)[PAGETBL_ENT]) {
    if (pagetbl_used == PAGEDIR_ENT) {
        panic("cannot allocate new page table");
    }
    *pagetbl = &pagetbl_alloc[++pagetbl_used];
}

void pgidentity(void) {
    u32 (*pagetbl)[PAGETBL_ENT];
    ptalloc(&pagetbl);

    for (size_t i = 0; i < PAGETBL_ENT; ++i) {
        (*pagetbl)[i] = (i * 0x1000) | PE_PRESENT(1) | PE_RW(1) | PE_US(0);
    }

    pagedir[0] = ((u32)pagetbl) | PE_PRESENT(1) | PE_RW(1) | PE_US(0);
}

void pgenable(void) {
    u32 cr0 = x86_cr0();
    if (cr0 & PG) {
        panic("paging is already enabled");
    }

    x86_write_cr3((u32) pagedir);
    x86_write_cr0(cr0 | PG);
}

void pginfo(struct pginfo *out) {
    u32 cr0 = x86_cr0();    
    out->enabled = (cr0 & PG) != 0;
}

void pginfo_debug(struct pginfo *info, string_t *buf) {
    string_pushcstr(buf, "pginfo { enabled=");
    string_pushcstr(buf, info->enabled ? "true" : "false");
    string_pushcstr(buf, " }");
}
