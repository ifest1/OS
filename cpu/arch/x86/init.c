
#include <screen.h>
#include <keyboard.h>
#include <timer.h>
#include <idt.h>
#include <pic.h>
#include <isr.h>

void x86_init() {
    fill_screen(BLACK_ON_WHITE);
    init_idt();
    init_pics();
    load_irq_handler(IRQ0, timer_handler);
    load_irq_handler(IRQ1, keyboard_handler);
    enable_interrupts();
}