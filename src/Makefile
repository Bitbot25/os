# CC=i686-elf-gcc
LLVM_TARGET=i386-pc-none-elf
CC=clang
CFLAGS=-target $(LLVM_TARGET) -I../include -std=c17 -Wall -Wextra -pedantic -ffreestanding -fno-stack-protector -mno-red-zone
LDFLAGS=-target $(LLVM_TARGET) 
OBJS=x86.o kernel.o head.o serial.o vga.o page.o string.o libkern.o
LDS=../linker.ld

qemu: kernel.bin
	qemu-system-i386 -serial stdio -kernel kernel.bin

iso: kernel.bin
	cp kernel.bin ../isodir/boot/kernel.bin
	grub-mkrescue -o ../kernel.iso ../isodir

kernel.bin: $(OBJS)
	$(CC) $(LDFLAGS) -T $(LDS) -o $@ -ffreestanding -nostdlib $(OBJS) 

clean:
	-rm $(OBJS)
	-rm kernel.bin

.PHONY: qemu iso clean
