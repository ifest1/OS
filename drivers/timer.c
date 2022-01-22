#include <stdlib.h>
#include <cpu/x86/idt.h>
#include <cpu/x86/isr.h>
#include <drivers/timer.h>
#include <drivers/screen.h>

void timer_handler(registers_t regs) {

}

void timer_install() {
    load_irq_handler(IRQ0, timer_handler);
}
