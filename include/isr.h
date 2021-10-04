#ifndef ISR_H__
#define ISR_H__
#include "../include/stdint.h"
#include "../include/idt.h"
typedef void (*isr_t)(registers_t);
void irq_handler(registers_t regs);
void load_irq_handler(uint8_t irq_no, isr_t handler);
#endif