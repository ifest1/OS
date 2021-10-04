#include "../include/pic.h"
#include "../include/ports.h"
#include "../include/stdint.h"

void init_pics() {
    // ICW1
    outb(PIC1_CMD, PIC_ICW1_INIT | PIC_ICW1_ICW4_PRESENT);
    outb(PIC2_CMD, PIC_ICW1_INIT | PIC_ICW1_ICW4_PRESENT);
    // ICW2 (Set PIC base IDT offset)
    outb(PIC1_DATA, PIC1_BASE_IDT_OFFSET);
    outb(PIC2_DATA, PIC2_BASE_IDT_OFFSET);
    // ICW3
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    // ICW4
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, 0x00);
    outb(PIC2_DATA, 0x00);
}

void pic_set_mask(uint8_t irq_line) {
    uint8_t mask;
    uint16_t port;
    if (irq_line < 7) {
        port = PIC1_DATA;
    }
    else {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    mask = inb(port) | (1 << irq_line);
    outb(port, mask);
}

void pic_clear_mask(uint8_t irq_line) {
    uint8_t mask;
    uint16_t port;
    if (irq_line < 7) {
        port = PIC1_DATA;
    }
    else {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    mask = inb(port) & ~(1 << irq_line);
    outb(port, mask);
}

void send_pic_eoi(uint8_t irq_line) {
    if (irq_line >= 40) {
        outb(PIC2_CMD, PIC_EOI);
    }
    outb(PIC1_CMD, PIC_EOI);
}