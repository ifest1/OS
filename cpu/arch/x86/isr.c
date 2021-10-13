#include <cpu/x86/isr.h>
#include <cpu/x86/pic.h>

isr_t           interrupt_handlers[256];

void irq_handler(registers_t regs) {
    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
    send_pic_eoi(regs.int_no);
}

void load_irq_handler(uint8_t irq_no, isr_t handler) {
    interrupt_handlers[irq_no] = handler;
}