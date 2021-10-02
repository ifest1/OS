#include "../include/pic.h"
#include "../include/irq.h"

// TODO (Reduce code duplication)
void enable_irq(uint8_t irq_line) {
    uint16_t pic_data_port;
    if (irq_line >= 7) {
        pic_data_port = PIC1_PORT_A + 1;
    }

    else if (8 <= irq_line <= 15) {
        pic_data_port = PIC2_PORT_A + 1;
        irq_line -= 8;
    }

    else return;

    pic_set_mask(irq_line, pic_data_port);
}

void disable_irq(uint8_t irq_line) {
    uint16_t pic_data_port;
    if (irq_line >= 7) {
        pic_data_port = PIC1_PORT_A + 1;
    }

    else if (8 <= irq_line <= 15) {
        pic_data_port = PIC2_PORT_A + 1;
        irq_line -= 8;
    }

    else return;
    pic_clear_mask(irq_line, pic_data_port);
}

void init_irq_lines() {
    for (int i = 0; i <= 15; i++) {
        enable_irq(i);
    }
}