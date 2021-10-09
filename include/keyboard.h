#include "./idt.h"
#include "./ports.h"

#ifndef KEYBOARD_H__
#define KEYBOARD_H__


void keyboard_handler(registers_t regs);

#endif