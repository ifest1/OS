# Operating System from scratch (educational purpose)

# [LICENSE](LICENSE)

# Notes

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

## System bus

The system bus is a combination of Data Bus, Address Bus and Control Bus,

### Data bus

The purpose of this bus it to transfer data between the system components.
The size varies from 16 bits, 32 bits, 64 bits.

### Address bus

A "Memory Address" is just a number used by the Memory Controller.
The Memory Controller takes the number from this bus, and interprets it as a memory location.
Knowing the size of each RAM chip The Memory Controller could easily
refrence the exact RAM chip and byte offset in it. Beginning with Memory Cell 0, the Memory
Controller intereprates this offset as the Address that we want.
The Address Bus is connected to the processor through the Control Unit (CU), and the I/O Controller. The Control Unit is inside the processor, so we will look at that later. The I/O Controller controls the interface to hardware devices.

### Control bus

The Control Bus is a series of lines/bits that represent what a device is trying to do. For example, the processor would set the READ bit or WRITE bit to let the Memory Controller know it wants to read or write the data in the Data Bus from the memory location stored in the Address Bus.

### Controllers

A Controller provides basic hardware control functionaility. It also provides the basic interface between hardware and software.

### Memory Controller

The Memory Controller provides a way of readng and writing memory locations through software. The Memory Controller is also responsible for the constant refreshing of the RAM chips to insure they retain the information.
Memory Controllers a Multiplexer and Demultiplexer circuits to select the exact RAM chip, and location that refrences the address in the Address Bus.

- Double Data Rate (DDR) Controller
  A DDR Controller is used to refresh DDR SDRAM, which uses the System Clock pulse to allow reading and writing memory.
- Dual Channel Controller
  A Dual Channel Controller are used where DRAM devices are seperated into two small busses, allowing reading and writing two memory locations at once. This helps increasing speed when accessing RAM.

## I/O Subsystem

The I/O SubSystem simply represents Port I/O. This is the basic system that provides the interface between software and hardware controllers.

### Ports

- A Hardware Port provides the interface between two physical devices. This port is useually a connection device of sorts. This includes, but is not limited to: Serial Ports, Parallel ports, PS/2 Ports, 1394, FireWire, USB Ports, etc.
  Two general classifications for Hardware Ports include "Male" and "Female" ports. Male ports are connections where the pins emerge from the connector. Female ports are the opposite of this. Hardware ports are accessed through Controllers. More on this later...

- THIS will be very important to us. This is our interface to the hardware. A Software Port is a number. Thats it. This number represents a hardware controller... Kind of. You may know that several port numbers could represent the same controller. The reason? Memory Mapped I/O.

## Memory mapping

## Next steps

- Interrupt Descriptor Table
- Keyboard interrupt routine

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
