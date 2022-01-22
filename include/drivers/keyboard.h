#include <cpu/x86/idt.h>
#include <cpu/x86/ports.h>

#ifndef KEYBOARD_H__
#define KEYBOARD_H__
#define BACKSPACE   0x0E
#define ENTER       0x1C
void keyboard_handler(registers_t regs);
void keyboard_install();
#endif