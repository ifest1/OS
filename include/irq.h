#include "../include/stdint.h"
#ifndef IRQ_H__
#define IRQ_H__
void enable_irq(uint8_t irq_line);
void disable_irq(uint8_t irq_line);
void init_irq_lines();
#endif