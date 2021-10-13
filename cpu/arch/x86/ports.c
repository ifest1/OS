#include <stdint.h>
#include <cpu/x86/ports.h>
/*
Source: https://wiki.osdev.org/Inline_Assembly
In the constraint, 'a' refers to EAX, 'b' to EBX, 'c' to ECX,
'd' to EDX, 'S' to ESI, and 'D' to EDI (read the GCC manual for a full list),
assuming that you are coding for the IA32 architecture. An equation sign
indicates that your assembly code does not care about the initial value
of the mapped variable (which allows some optimization).
*/

// Port write byte
void outb(uint16_t port, uint8_t data) {
    __asm__ volatile ("out %%al, %%dx" : : "a" (data), "d" (port));
}

// Port read byte
uint8_t inb(uint16_t port) {
    uint8_t data;
    __asm__ volatile ("in %%dx, %%al": "=a" (data) : "d" (port));
    return data;
}

// Port write word
void outw(uint16_t port, uint32_t data) {
    __asm__ volatile ("out %%al, %%dx": : "a" (data), "d" (port));
}

// Port read word
uint32_t inw(uint16_t port) {
    uint32_t data;
    __asm__ volatile ("in %%dx, %%al" : "=a" (data) : "d" (port));
    return data;
}