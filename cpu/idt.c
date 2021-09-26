#include "../include/stdint.h"
#include "../include/idt.h"

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

    idtr.limit = (uint16_t) 256 * sizeof(idtr) - 1;
    idtr.base_address = (uint32_t) & idt;
    __asm__ volatile ("lidtl (%0)": : "r" (&idtr));
    __asm__ volatile ("sti");
}

void load_isr(uint16_t irq_id, uint32_t isr) {
    idt[irq_id].offset_low = (uint16_t) ((isr) & 0xFFFF);
    idt[irq_id].offset_high = (uint16_t) (((isr) >> 16) & 0xFFFF);
    idt[irq_id].unused = 0x00;
    idt[irq_id].selector = 0x08;
    idt[irq_id].type = 0x8E;
}
