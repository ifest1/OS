rm disk.img &&
nasm bootloader.asm -f bin -o bootloader &&
nasm sample.asm -f bin -o sample &&
dd if=/dev/zero of=disk.img bs=512 count=2880 &&
dd conv=notrunc if=bootloader of=disk.img bs=512 count=1 seek=0 &&
dd conv=notrunc if=sample of=disk.img bs=512 count=1 seek=1 &&
qemu-system-i386 -machine q35 -fda disk.img
#qemu-system-i386 -fda disk.img

