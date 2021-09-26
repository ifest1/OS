C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
OBJ_FILES = $(C_SOURCES:.c=.o cpu/interrupt.o)
CFLAGS = -fno-pie -ffreestanding

%.o: %.asm
	nasm $< -f elf32 -o $@

%.o: %.c
	gcc -m32 ${CFLAGS} -c $< -o $@

%.bin : %.asm
	nasm $< -f bin -I '../../16bit/' -o $@

os.img: boot/bootloader.bin kernel/kernel.bin
	cat $^ > os-image.bin

kernel/kernel.bin: kernel/kernel_entry.o ${OBJ_FILES}
	ld -o $@ -m elf_i386 -Ttext 0x1000 $^ --oformat binary

run:
	make clean
	make build
	qemu-system-i386 -machine q35 -fda os-image.bin
	make clean

build: os.img

clean:
	rm -fr *.bin *.o *.img
	rm -fr kernel/*.o boot/*.bin drivers/*.o cpu/*.o

