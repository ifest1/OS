#include <mm/mm.h>
#include <stdlib.h>

void print_mm_entries(mmap_entry_t **entries, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        char buf[10];
        itoa(entries[i]->base_addr_low, 16, buf);
        printk(buf, 0);
        itoa(entries[i]->base_addr_high, 16, buf);
        printk(buf, 1);
    }
}

void set_usable_mm() {

}

