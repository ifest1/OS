
#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/keyboard.h"
#include "../include/screen.h"
#include "../include/timer.h"
#include "../include/mm.h"
#include "../include/pic.h"
#include "../lib/utils.h"
#include "../lib/print.h"

void main() {
    fill_screen(BLACK_ON_WHITE);
    init_idt();
    init_pics();
    load_irq_handler(IRQ0, timer_handler);
    load_irq_handler(IRQ1, keyboard_handler);
    enable_interrupts();
}