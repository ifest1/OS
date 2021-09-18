# Operating System from scratch

# [LICENSE](LICENSE)

## Bootloader

The bootloader is the first piece of code that the system runs.
The BIOS looks at the last 2 bytes of the disk's first sector,
if this two bytes matches the magic number (0xAA55) then its
a bootable disk. Once the system is booted the bootloader can
access some BIOS subroutines to read bytes from disk, print
characters in the screen, etc.

## Real mode

The system boots up in Real Mode, in this mode we can access BIOS
routines but we are unable to access more than 1MB of memory. There
is some securities implications in this mode as well, in this we don't
have hardware-based memory protection like GDT. Memory addressing is very
difficult in this mode since we have to use segment register to access
memory addresses above 64K.

## Protected mode

In this mode we can access higher memory addresses without concerning about
segment registers. This mode also allow us to define how our memory will be
accessed, memory access privileges, etc.

## GDT

To be able to switch to protected mode we must load a descriptor table to the CPU
to tell the CPU how the memory will be accessed (segments, memory protection). Once
we load the GDT we are officially in protected mode.

## IDT

There is also another structure that we need to tell to the CPU when we switch to protected
mode: IDT, this describes a table of vectors storing some interrupt service routines addresses.
If we switched to protected mode we will need to load this structure since we can't access the
BIOS interrupt service routines anymore.

## Graphics

The VGA is mapped into the main memory, in other words, the device controller memory can be accessed
from the RAM, specifically 0xb8000 is the beginning of the screen. Each 2 bytes we can define a
character (1 byte) and background and foreground color (remaining 1 byte).

# TODO

- [x] GDT
- [ ] IDT
- [ ] Keyboard
- [ ] PIT
- [ ] RTC
- [ ] Iinitrd
- [ ] Drawing on framebuffer
- [ ] Serial debugging
- [ ] VFS
- [ ] Paging
- [ ] Heap
- [ ] PMM
- [ ] VMM
- [ ] ACPI
- [ ] Shutdown
- [ ] Reboot
- [ ] HPET
- [ ] PCI
- [ ] AHCI
- [ ] Real filesystems (ext2, fat...)
- [ ] Multithreading
- [ ] TSS
- [ ] Userspace
- [ ] System calls
- [ ] POSIX
- [ ] ELF execution
- [ ] Port libc (Newlib)
- [ ] Port apps
- [ ] Sound
- [ ] Network
- [ ] USB
- [ ] GUI

## Notes

- Looks like the constants must defined at the bottom of the ASM file.
- Include other ASM files as well.

## Next steps

- Clear the screen with blue blackground
- Write print string on protected mode
- Build the kernel using Makefile
- Pass the control to some high level language

## Resources

https://wiki.osdev.org/
https://github.com/ghaiklor/awesome-internals
https://github.com/ghaiklor/ghaiklor-os-gcc
http://www.brokenthorn.com/Resources/OSDevIndex.html
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
https://github.com/Absurdponcho/PonchoOS
https://www.youtube.com/channel/UCQdZltW7bh1ta-_nCH7LWYw
https://www.youtube.com/watch?v=7LTB4aLI7r0&list=PLxN4E629pPnKKqYsNVXpmCza8l0Jb6l8-
https://www.youtube.com/watch?v=5FnrtmJXsdM&list=PLT7NbkyNWaqajsw8Xh7SP9KJwjfpP8TNX
