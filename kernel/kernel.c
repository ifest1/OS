
#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/keyboard.h"
#include "../include/screen.h"
#include "../include/timer.h"
#include "../lib/utils.h"
#include "../lib/print.h"

void main() {
    fill_screen(WHITE_ON_BLUE);
    init_idt();
    init_pics();
    load_irq_handler(IRQ0, timer_handler);
    load_irq_handler(IRQ1, keyboard_handler);
    enable_interrupts();
}