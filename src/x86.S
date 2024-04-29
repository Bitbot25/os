#include "asm.h"

ENTRY(inb)
    // argument in esp+8
    movl 4(%esp), %edx // port
    xorl %eax, %eax
    inb %dx
    ret

ENTRY(outb)
    // argument in esp+8
    movzwl 4(%esp), %edx // port
    movzbl 8(%esp), %eax // value
    outb %dx
    ret

ENTRY(lgdt)
    movl 4(%esp), %edx
    lgdt (%edx)
    ret
