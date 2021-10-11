
#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/keyboard.h"
#include "../include/screen.h"
#include "../include/timer.h"
#include "../include/mm.h"
#include "../include/pic.h"
#include "../lib/utils.h"
#include "../lib/print.h"
#include "../lib/sort.h"

void main() {
    fill_screen(BLACK_ON_WHITE);
    init_idt();
    init_pics();
    load_irq_handler(IRQ0, timer_handler);
    load_irq_handler(IRQ1, keyboard_handler);
    enable_interrupts();

    for (uint8_t i = 0; i < MMAP_ENTRY_COUNT; i++) {
        mmap_entry_t *mm_entry = (mmap_entry_t *) &MMAP_ENTRY + i;
        print_mmap(mm_entry);
    }
}