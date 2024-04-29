#include "asm.h"

.set ALIGN,     1<<0
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
multiboot_end:

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

ENTRY(_start)
    mov $stack_top, %esp
    pushl $0
    popf

    call kern32

    cli
1:  hlt
    jmp 1b

.size _start, . - _start
