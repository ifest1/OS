
#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/keyboard.h"
#include "../include/screen.h"
#include "../include/timer.h"
#include "../lib/print.h"
#include "../lib/utils.h"

void main() {
    init_idt();
    init_pics();
    fill_screen(WHITE_ON_BLUE);
    load_irq_handler(IRQ0, timer_driver);
    load_irq_handler(IRQ1, keyboard_driver);
    enable_interrupts();
    printk("from kernel");
    printk("embaixo");
    printk("embaixo3");
}