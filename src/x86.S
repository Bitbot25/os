#include <os/asm.h>

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

ENTRY(x86_reload_code_selector)
    mov 4(%esp), %eax
    push %eax // push cs 
    push $.reload_cs // push target
    lret
.reload_cs:
    ret

ENTRY(x86_reload_misc_selectors)
    mov 4(%esp), %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ret

ENTRY(x86_abort)
    cli
.hlt:
    hlt
    jmp .hlt

ENTRY(x86_cr0)
    movl %cr0, %eax
    ret

ENTRY(x86_write_cr0)
    mov 4(%esp), %eax
    mov %eax, %cr0
    ret

ENTRY(x86_cr3)
    movl %cr3, %eax
    ret

ENTRY(x86_write_cr3)
    mov 4(%esp), %eax
    mov %eax, %cr3
    ret

ENTRY(x86_cr4)
    movl %cr4, %eax
    ret

ENTRY(x86_write_cr4)
    mov 4(%esp), %eax
    mov %eax, %cr4
    ret
