C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
OBJ_FILES = $(C_SOURCES:.c=.o)

%.o: %.asm
	nasm $< -f elf32 -o $@

%.o: %.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

%.bin : %.asm
	nasm $< -f bin -I '../../16bit/' -o $@

kernel.bin: kernel/kernel_entry.o ${OBJ_FILES}
	ld -o $@ -m elf_i386 -Ttext 0x1000 $< $(word 2, $^) --oformat binary

disk.img: boot/bootloader.bin kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880 && \
	dd conv=notrunc if=$< of=$@ bs=512 count=1 seek=0 && \
	dd conv=notrunc if=$(word 2, $^) of=$@ bs=512 count=1 seek=1

run:
	qemu-system-i386 -machine q35 -fda disk.img

build:
	make disk.img

clean:
	rm -fr *.bin *.o
	rm -fr kernel/*.o boot/*.bin drivers/*.o

