#include <stdint.h>

#ifndef IDT_H__
#define IDT_H__

#define IRQ0                    32
#define IRQ1                    33
#define IRQ2                    34
#define IRQ3                    35
#define IRQ4                    36
#define IRQ5                    37
#define IRQ6                    38
#define IRQ7                    39
#define IRQ8                    40
#define IRQ9                    41
#define IRQ10                   42
#define IRQ11                   43
#define IRQ12                   44
#define IRQ13                   45
#define IRQ14                   46
#define IRQ15                   47

typedef struct {
    uint16_t                offset_low;
    uint16_t                selector;
    uint8_t                 unused;
    uint8_t                 type;
    uint16_t                offset_high;
} __attribute__((packed)) idt_entry_t;


typedef struct {
    uint16_t                limit;
    uint32_t                base_address;
} __attribute__((packed)) idtr_t;

typedef struct registers
{
    uint32_t                 ds;
    uint32_t                 edi;
    uint32_t                 esi;
    uint32_t                 ebp;
    uint32_t                 esp;
    uint32_t                 ebx;
    uint32_t                 edx;
    uint32_t                 ecx;
    uint32_t                 eax;
    uint32_t                 int_no;
    uint32_t                 err_code;
    uint32_t                 eip;
    uint32_t                 cs;
    uint32_t                 eflags;
    uint32_t                 useresp;
    uint32_t                 ss;
} registers_t;

void init_idt();
void load_isr(uint16_t irq_id, uint32_t isr);
void enable_interrupts();
void disable_interrupts();
#endif