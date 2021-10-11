#include "../include/idt.h"
#include "../include/ports.h"
#include "../include/screen.h"
#include "../include/pic.h"
#include "../include/isr.h"
#include "../lib/print.h"

idtr_t          idt_ptr;
idt_entry_t     idt[256];

void enable_interrupts() {
    __asm__ volatile ("sti");
}

void disable_interrupts() {
    __asm__ volatile ("cli");
}

void idt_flush() {
    __asm__ volatile ("lidtl (%0)": : "m" (idt_ptr));
}

void set_idt_gate(uint16_t irq_id, uint32_t isr, uint16_t sel, uint8_t flags) {
    idt[irq_id].offset_low      = (uint16_t) ((isr) & 0xFFFF);
    idt[irq_id].offset_high     = (uint16_t) (((isr) >> 16) & 0xFFFF);
    idt[irq_id].unused          = 0x00;
    idt[irq_id].selector        = sel;
    idt[irq_id].type            = flags;
}

void init_idt() {
    idt_ptr.limit               = (uint16_t) 256 * sizeof(idt_entry_t) - 1;
    idt_ptr.base_address        = (uint32_t) & idt;
    set_idt_gate(0, (uint32_t) isr0, 0x08, 0x8E);
    set_idt_gate(1, (uint32_t) isr1, 0x08, 0x8E);
    set_idt_gate(2, (uint32_t) isr2, 0x08, 0x8E);
    set_idt_gate(3, (uint32_t) isr3, 0x08, 0x8E);
    set_idt_gate(4, (uint32_t) isr4, 0x08, 0x8E);
    set_idt_gate(5, (uint32_t) isr5, 0x08, 0x8E);
    set_idt_gate(6, (uint32_t) isr6, 0x08, 0x8E);
    set_idt_gate(7, (uint32_t) isr7, 0x08, 0x8E);
    set_idt_gate(8, (uint32_t) isr8, 0x08, 0x8E);
    set_idt_gate(9, (uint32_t) isr9, 0x08, 0x8E);
    set_idt_gate(10, (uint32_t) isr10, 0x08, 0x8E);
    set_idt_gate(11, (uint32_t) isr11, 0x08, 0x8E);
    set_idt_gate(12, (uint32_t) isr12, 0x08, 0x8E);
    set_idt_gate(13, (uint32_t) isr13, 0x08, 0x8E);
    set_idt_gate(14, (uint32_t) isr14, 0x08, 0x8E);
    set_idt_gate(15, (uint32_t) isr15, 0x08, 0x8E);
    set_idt_gate(16, (uint32_t) isr16, 0x08, 0x8E);
    set_idt_gate(17, (uint32_t) isr17, 0x08, 0x8E);
    set_idt_gate(18, (uint32_t) isr18, 0x08, 0x8E);
    set_idt_gate(19, (uint32_t) isr19, 0x08, 0x8E);
    set_idt_gate(20, (uint32_t) isr20, 0x08, 0x8E);
    set_idt_gate(21, (uint32_t) isr21, 0x08, 0x8E);
    set_idt_gate(22, (uint32_t) isr22, 0x08, 0x8E);
    set_idt_gate(23, (uint32_t) isr23, 0x08, 0x8E);
    set_idt_gate(24, (uint32_t) isr24, 0x08, 0x8E);
    set_idt_gate(25, (uint32_t) isr25, 0x08, 0x8E);
    set_idt_gate(26, (uint32_t) isr26, 0x08, 0x8E);
    set_idt_gate(27, (uint32_t) isr27, 0x08, 0x8E);
    set_idt_gate(28, (uint32_t) isr28, 0x08, 0x8E);
    set_idt_gate(29, (uint32_t) isr29, 0x08, 0x8E);
    set_idt_gate(30, (uint32_t) isr30, 0x08, 0x8E);
    set_idt_gate(31, (uint32_t) isr31, 0x08, 0x8E);
    set_idt_gate(32, (uint32_t) isr32, 0x08, 0x8E);
    set_idt_gate(33, (uint32_t) isr33, 0x08, 0x8E);
    set_idt_gate(34, (uint32_t) isr34, 0x08, 0x8E);
    set_idt_gate(35, (uint32_t) isr35, 0x08, 0x8E);
    set_idt_gate(36, (uint32_t) isr36, 0x08, 0x8E);
    set_idt_gate(37, (uint32_t) isr37, 0x08, 0x8E);
    set_idt_gate(38, (uint32_t) isr38, 0x08, 0x8E);
    set_idt_gate(39, (uint32_t) isr39, 0x08, 0x8E);
    set_idt_gate(40, (uint32_t) isr40, 0x08, 0x8E);
    set_idt_gate(41, (uint32_t) isr41, 0x08, 0x8E);
    set_idt_gate(42, (uint32_t) isr42, 0x08, 0x8E);
    set_idt_gate(43, (uint32_t) isr43, 0x08, 0x8E);
    set_idt_gate(44, (uint32_t) isr44, 0x08, 0x8E);
    set_idt_gate(45, (uint32_t) isr45, 0x08, 0x8E);
    set_idt_gate(46, (uint32_t) isr46, 0x08, 0x8E);
    set_idt_gate(47, (uint32_t) isr47, 0x08, 0x8E);
    printk("IDT Gates loaded.");
    idt_flush();
    printk("CPU IDT Pointer loaded.");
}
