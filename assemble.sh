dd if=/dev/zero of=disk.img bs=512 count=2880 &&
nasm boot/bootloader.asm -f bin -o bootloader.bin &&
nasm kernel/kernel_entry.asm -f elf32 -o kernel_entry.o &&
gcc -m32 -fno-pie -ffreestanding -c kernel/kernel.c -o kernel.o &&
ld -o kernel.bin -m elf_i386 -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary &&
dd conv=notrunc if=bootloader.bin of=disk.img bs=512 count=1 seek=0 &&
dd conv=notrunc if=kernel.bin of=disk.img bs=512 count=1 seek=1 &&
qemu-system-i386 -machine q35 -fda disk.img
rm kernel.bin; rm bootloader.bin; rm kernel.o; rm kernel_entry.o; rm disk.img