
#include "../include/idt.h"
#include "../include/keyboard.h"
#include "../include/screen.h"
#include "../include/timer.h"
#include "../lib/print.h"
#include "../lib/utils.h"

void main() {
    init_idt();
    load_irq_handler(IRQ0, timer_driver);
    load_irq_handler(IRQ1, keyboard_driver);
    printk("from kernel", VIDEO_MEMORY + 200);
}