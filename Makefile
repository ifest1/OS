C_SOURCES 	= $(wildcard kernel/*.c drivers/*.c cpu/arch/x86/*.c lib/*.c)
OBJ_FILES 	= $(C_SOURCES:.c=.o cpu/arch/x86/interrupt.o boot/mmap.o kernel/kernel_entry.o)

CFLAGS 		= -fno-pie -ffreestanding -m32 -I include
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

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	${ASM} $< ${ASMFLAGS} -o $@

%.bin: %.asm
	${ASM} $< ${BINFLAGS} -o $@

${word 2, $(BINARIES)}: ${OBJ_FILES}
	${LINKER} -o $@ ${LDFLAGS} $^

${IMAGE}: ${BINARIES}
	cat $^ > ${IMAGE}

build: ${IMAGE}
	${QEMU} ${QEMUFLAGS} ${IMAGE}
	make clean

clean:
	rm -fr ${BINARIES} ${OBJ_FILES}

