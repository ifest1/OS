#include <mm/mm.h>
#include <stdlib.h>

void print_mm_entries(mmap_entry_t *entry, uint32_t size) {
    char buf[10];
    for (uint32_t i = 0; i < size; i++) {
        if (entry->type == 0) break;
        itoa(entry->type, 10, buf);
        printk("Type: ", 0);
        printk(buf, 0);
        printk(" ", 0);
        itoa(entry->base_addr_high, 16, buf);
        printk("Address: ", 0);
        printk(buf, 0);
        itoa(entry->base_addr_low, 16, buf);
        printk(buf, 1);
        entry++;
    }
}

void set_usable_mm(mmap_entry_t *entry, uint32_t size) {
    uint32_t i = 0;
    char buf[4];
    while (i < size && entry->type != 0) {
        if (entry->type == 1) {
            usable_memory[i] = entry;
            itoa(entry->type, 10, buf);
            printk("Type: ", 0);
            printk(buf, 0);
            printk(" ", 0);
            itoa(entry->base_addr_high, 16, buf);
            printk("Address: ", 0);
            printk(buf, 0);
            itoa(entry->base_addr_low, 16, buf);
            printk(buf, 1);
            i++;
        }
        entry++;
    }
}

