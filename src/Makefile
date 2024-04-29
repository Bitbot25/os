CC=i686-elf-gcc
CFLAGS=-Wall -Wextra -ffreestanding
OBJS=x86.o kernel.o head.o serial.o vga.o
LDS=../linker.ld

kernel.bin: $(OBJS)
	$(CC) -T $(LDS) -o $@ -ffreestanding -nostdlib -lgcc $^
clean:
	-rm $(OBJS)
	-rm kernel.bin

.PHONY: clean
