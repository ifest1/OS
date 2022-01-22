IMAGE			= kernel/kernel.bin
OS 				= os.bin
SRCFILES 		= $(shell find -type f -name "*.c")
LINKFILES		= cpu/arch/x86/i386.o
OBJFILES 		= $(patsubst %.c,%.o,$(SRCFILES) $(LINKFILES))

CFLAGS 			= -Wall -Wextra -std=c99 -m32 -nostdlib -fno-builtin \
		 		  -ffreestanding -fno-pie -I include
ASMFLAGS 		= -f elf32
LDFLAGS 		= -g -n -melf_i386 -T link.ld -Map System.map
QEMUFLAGS		= -kernel ${IMAGE}
LINKFILE		= link.ld

CC 				= gcc
ASM				= nasm
LD				= ld
QEMU			= qemu-system-i386
GDB				= gdb

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	${ASM} $< ${ASMFLAGS} -o $@

%.bin: %.asm
	${ASM} $< ${BINFLAGS} -o $@

${IMAGE}: ${OBJFILES}
	${LD} -o $@ ${LDFLAGS} $^

build: ${IMAGE}
	${CC} -T ${LINKFILE} -o ${OS} ${CFLAGS} ${OBJFILES}

iso: build
	mkdir -p isodir/boot/grub
	cp ${OS} isodir/boot/${OS}
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o os.iso isodir

run:
	${QEMU} ${QEMUFLAGS} ${OS}

clean:
	rm -fr ${KERNEL} ${OS} ${OBJFILES}
