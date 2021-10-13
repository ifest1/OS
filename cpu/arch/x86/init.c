
#include <drivers/screen.h>
#include <drivers/keyboard.h>
#include <drivers/timer.h>
#include <cpu/x86/idt.h>
#include <cpu/x86/pic.h>
#include <cpu/x86/isr.h>

void x86_init() {
    fill_screen(BLACK_ON_WHITE);
    init_idt();
    init_pics();
    load_irq_handler(IRQ0, timer_handler);
    load_irq_handler(IRQ1, keyboard_handler);
    enable_interrupts();
}