#include "../include/pic.h"
#include "../include/ports.h"
#include "../include/stdint.h"

void init_pics() {
    // Tell to master PIC the IRQ line used by slave and tell slave his identity.
    uint8_t mpic_slv_irq_l  =     0x04;
    uint8_t slvpic_id       =     0x02;

    // Save PIC masks
    uint8_t mask_PIC1 = inb(PIC1_PORT_B);
    uint8_t mask_PIC2 = inb(PIC2_PORT_B);

    // ICW1
    outb(PIC1_PORT_A, PIC_ICW1_INIT | PIC_ICW1_ICW4_PRESENT);
    outb(PIC2_PORT_A, PIC_ICW1_INIT | PIC_ICW1_ICW4_PRESENT);

    // ICW2 (Set PIC base IDT offset)
    outb(PIC1_PORT_B, PIC1_BASE_IDT_OFFSET);
    outb(PIC2_PORT_B, PIC2_BASE_IDT_OFFSET);

    // ICW3
    outb(PIC1_PORT_B, mpic_slv_irq_l);
    outb(PIC2_PORT_B, slvpic_id);

    // ICW4
    outb(PIC1_PORT_B, ICW4_8086);
    outb(PIC2_PORT_B, ICW4_8086);

    // Restore PICs masks
    outb(PIC1_PORT_B, mask_PIC1);
    outb(PIC2_PORT_B, mask_PIC2);
}

void pic_set_mask(uint8_t irq_line, uint16_t pic_cmd_port) {
    uint8_t mask = inb(pic_cmd_port);
    outb(pic_cmd_port, mask | (1 << irq_line));
}

void pic_clear_mask(uint8_t irq_line, uint16_t pic_cmd_port) {
    uint8_t mask = inb(pic_cmd_port);
    outb(pic_cmd_port, mask & ~(1 << irq_line));
}