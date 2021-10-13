SRCFILES 	= $(shell find $(PROJDIRS) -type f -name "*.c")
LINKFILES	= cpu/arch/x86/interrupt.o boot/mmap.o kernel/kernel_entry.o
OBJFILES 	= $(patsubst %.c,%.o,$(SRCFILES) $(LINKFILES))

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

${word 2, $(BINARIES)}: ${OBJFILES}
	${LINKER} -o $@ ${LDFLAGS} $^

${IMAGE}: ${BINARIES}
	cat $^ > ${IMAGE}

build: ${IMAGE}
	${QEMU} ${QEMUFLAGS} ${IMAGE}
	make clean

clean:
	rm -fr ${BINARIES} ${OBJFILES}

