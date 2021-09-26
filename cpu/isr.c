#include "../include/isr.h"

void isr_handler(registers_t regs) {
    __asm__ volatile ("cli");
}