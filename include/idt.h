#include "stdint.h"

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

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();
extern void isr41();
extern void isr42();
extern void isr43();
extern void isr44();
extern void isr45();
extern void isr46();
extern void isr47();

#endif