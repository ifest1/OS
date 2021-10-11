C_SOURCES 	= $(wildcard kernel/*.c drivers/*.c cpu/*.c lib/*.c)
OBJ_FILES 	= $(C_SOURCES:.c=.o cpu/interrupt.o boot/mmap.o kernel/kernel_entry.o)
CFLAGS 		= -fno-pie -ffreestanding -m32
ASMFLAGS 	= -f elf32
BINFLAGS	= -f bin -I '../../16bit/'
LDFLAGS 	= -m elf_i386 -Ttext 0x1000 --oformat binary
BINARIES	= boot/bootloader.bin kernel/kernel.bin
IMAGE 		= os-image.bin
CC 			= gcc
ASM			= nasm

%.o: %.asm
	nasm $< ${ASMFLAGS} -o $@

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.bin : %.asm
	${ASM} $< ${BINFLAGS} -o $@

kernel/kernel.bin: ${OBJ_FILES}
	ld -o $@ ${LDFLAGS} $^

os.img: ${BINARIES}
	cat $^ > ${IMAGE}

run: os.img
	qemu-system-i386 -machine q35 -fda os-image.bin
	make clean

clean:
	rm -fr *.bin *.o *.img kernel/*.o boot/*.bin drivers/*.o cpu/*.o lib/*.o

