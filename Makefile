C_SOURCES 	= $(wildcard kernel/*.c drivers/*.c cpu/*.c lib/*.c)
OBJ_FILES 	= $(C_SOURCES:.c=.o cpu/interrupt.o boot/mmap.o kernel/kernel_entry.o)
CFLAGS 		= -fno-pie -ffreestanding -m32
ASMFLAGS 	= -f elf32
BINFLAGS	= -f bin -I '../../16bit/'
LDFLAGS 	= -m elf_i386 -Ttext 0x1000 --oformat binary
QEMUFLAGS	= -machine q35 -fda
BINARIES	= boot/bootloader.bin kernel/kernel.bin
IMAGE 		= os-image.bin
CC 			= gcc
ASM			= nasm
LINKER		= ld
QEMU		= qemu-system-i386

%.o: %.asm
	nasm $< ${ASMFLAGS} -o $@

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.bin : %.asm
	${ASM} $< ${BINFLAGS} -o $@

kernel/kernel.bin: ${OBJ_FILES}
	${LINKER} -o $@ ${LDFLAGS} $^

os.img: ${BINARIES}
	cat $^ > ${IMAGE}

run: os.img
	${QEMU} ${QEMUFLAGS} ${IMAGE}
	make clean

clean:
	rm -fr ${BINARIES} ${OBJ_FILES}

