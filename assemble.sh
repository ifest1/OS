nasm bootloader.asm -f bin -o bootloader.bin &&
nasm kernel.asm -f bin -o kernel.bin &&
dd if=/dev/zero of=bootloader.img bs=512 count=2880 &&
dd conv=notrunc if=bootloader.bin of=bootloader.img bs=512 count=1 seek=0 &&
dd conv=notrunc if=kernel.bin of=bootloader.img bs=512 count=1 seek=1 &&
qemu-system-i386 -machine q35 -fda bootloader.img
rm kernel.bin && rm bootloader.bin
#qemu-system-i386 -fda bootloader.img


