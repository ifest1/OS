#include "../include/keyboard.h"
#include "../cpu/ports.c"

void keyboard_driver(registers_t regs) {
    uint8_t scancode = inb(0x60);
}