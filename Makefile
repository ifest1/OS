C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
OBJ_FILES = $(C_SOURCES:.c=.o)

bootloader.bin: bootloader.asm
	nasm $< -f bin -o $@

kernel.o: kernel.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

kernel.entry.o: kernel_entry.asm
	nasm $< -f elf32 -o $@

kernel.bin: kernel_entry.o kernel.o
	ld -o kernel.bin -m elf_i386 -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary

disk.img: bootloader.bin kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880 &&
	dd conv=notrunc if=$< of=disk.img bs=512 count=1 seek=0 &&
	dd conv=notrunc if=$(word 2, $^) of=disk.img bs=512 count=1 seek=1

clean:
	rm *.bin *.o

qemu:
	qemu-system-i386 -machine q35 -fda disk.img

