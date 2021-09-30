#include "../include/idt.h"
#include "../include/ports.h"
#include "../include/screen.h"
#include "../lib/print.h"


/*
Low level functions to map the IRQ's to ISR's defined in ASM. This low level ISR's are calling
a common stub routine  that sets the stack and registers and pass the control to a higher level IRQ
handler.
*/
void load_isr(uint16_t irq_id, uint32_t isr) {
    idt[irq_id].offset_low = (uint16_t) ((isr) & 0xFFFF);
    idt[irq_id].offset_high = (uint16_t) (((isr) >> 16) & 0xFFFF);
    idt[irq_id].unused = 0x00;
    idt[irq_id].selector = 0x08;
    idt[irq_id].type = 0x8E;
}

void init_idt() {
    load_isr(0, (uint32_t) isr0);
    load_isr(1, (uint32_t) isr1);
    load_isr(2, (uint32_t) isr2);
    load_isr(3, (uint32_t) isr3);
    load_isr(4, (uint32_t) isr4);
    load_isr(5, (uint32_t) isr5);
    load_isr(6, (uint32_t) isr6);
    load_isr(7, (uint32_t) isr7);
    load_isr(8, (uint32_t) isr8);
    load_isr(9, (uint32_t) isr9);
    load_isr(10, (uint32_t) isr10);
    load_isr(11, (uint32_t) isr11);
    load_isr(12, (uint32_t) isr12);
    load_isr(13, (uint32_t) isr13);
    load_isr(14, (uint32_t) isr14);
    load_isr(15, (uint32_t) isr15);
    load_isr(16, (uint32_t) isr16);
    load_isr(17, (uint32_t) isr17);
    load_isr(18, (uint32_t) isr18);
    load_isr(19, (uint32_t) isr19);
    load_isr(20, (uint32_t) isr20);
    load_isr(21, (uint32_t) isr21);
    load_isr(22, (uint32_t) isr22);
    load_isr(23, (uint32_t) isr23);
    load_isr(24, (uint32_t) isr24);
    load_isr(25, (uint32_t) isr25);
    load_isr(26, (uint32_t) isr26);
    load_isr(27, (uint32_t) isr27);
    load_isr(28, (uint32_t) isr28);
    load_isr(29, (uint32_t) isr29);
    load_isr(30, (uint32_t) isr30);
    load_isr(31, (uint32_t) isr31);

    // PIC remapping
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);

    load_isr(32, (uint32_t) isr32);
    load_isr(33, (uint32_t) isr33);
    load_isr(34, (uint32_t) isr34);
    load_isr(35, (uint32_t) isr35);
    load_isr(36, (uint32_t) isr36);
    load_isr(37, (uint32_t) isr37);
    load_isr(38, (uint32_t) isr38);
    load_isr(39, (uint32_t) isr39);
    load_isr(40, (uint32_t) isr40);
    load_isr(41, (uint32_t) isr41);
    load_isr(42, (uint32_t) isr42);
    load_isr(43, (uint32_t) isr43);
    load_isr(44, (uint32_t) isr44);
    load_isr(45, (uint32_t) isr45);
    load_isr(46, (uint32_t) isr46);
    load_isr(47, (uint32_t) isr47);


    idtr.limit = (uint16_t) 256 * sizeof(idtr) - 1;
    idtr.base_address = (uint32_t) & idt;
    __asm__ volatile ("lidtl (%0)": : "r" (&idtr));
    __asm__ volatile ("sti");
}


/*
High level handler functions API, the functions below deals with registering IRQ handlers and
handling IRQs.
*/

isr_t irq_handlers[256];

void irq_handler(registers_t regs) {
    //char *curr_irq = itoa(irq_handlers_loaded);
    //printk(curr_irq, VIDEO_MEMORY);
    //irq_handlers_loaded++;
    if (irq_handlers[regs.int_no] != 0) {
        isr_t handler = irq_handlers[regs.int_no];
        handler(regs);
    }
}

void load_irq_handler(uint8_t irq_no, isr_t handler) {
    printk(itoa(irq_no), VIDEO_MEMORY);
    irq_handlers[irq_no] = handler;
}
