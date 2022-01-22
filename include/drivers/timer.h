#include <cpu/x86/idt.h>

#ifndef TIMER_H__
#define TIMER_H__
void timer_handler(registers_t regs);
void timer_install();
#endif
