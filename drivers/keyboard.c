#include "../include/keyboard.h"
#include "../include/ports.h"
#include "../include/screen.h"
#include "../lib/print.h"

void keyboard_driver(registers_t regs) {
    uint8_t scancode = inb(0x60);
    printk("teste", VIDEO_MEMORY + 120);
}