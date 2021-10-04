#include "stdint.h"
#ifndef PIC_H__
#define PIC_H__
#define PIC1_CMD                0x20        // Control port PIC1
#define PIC2_CMD                0xA0        // Control port PIC2

#define PIC1_DATA               0x21        // Data port PIC1
#define PIC2_DATA               0xA1        // Data port PIC2

#define PIC1_BASE_IDT_OFFSET    0x20        // PIC1 IDT interrupts offset after remapping
#define PIC2_BASE_IDT_OFFSET    0x28        // PIC2 IDT interrupts offset after remapping

#define PIC_ICW1_ICW4_PRESENT   0x01        // set = ICW4 needed, unset = ICW4 not needed
#define PIC_ICW1_SINGLE_MODE    0x02        // set = Single mode, unset = Cascade mode
#define PIC_ICW1_LEVEL          0x08        // set = Triggered mode, unset = Edge mode
#define PIC_ICW1_INIT           0x10        // ICW mask for PIC initialization

#define ICW4_8086	            0x01		// 8086/88 (MCS-80/85) mode
#define ICW4_AUTO	            0x02		// Auto (normal) EOI
#define ICW4_BUF_SLAVE	        0x08		// Buffered mode/slave
#define ICW4_BUF_MASTER	        0x0C		// Buffered mode/master
#define ICW4_SFNM	            0x10		// Special fully nested (not)

#define PIC_EOI		            0x20        // End of interrupt

void init_pics();
void pic_set_mask(uint8_t irq_line);
void pic_clear_mask(uint8_t irq_line);
#endif