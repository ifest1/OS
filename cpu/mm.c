#include "../include/mm.h"
#include "../lib/utils.h"
#include "../lib/print.h"

void print_mmap(mmap_entry_t *mmap) {
    printk(itoa(mmap->base_addr, 16, 10));
    printk(itoa(mmap->length, 16, 10));
    printk(itoa(mmap->type, 16, 10));
    printk("==============================");
}

// mmap_entry *order_mmap(mmap_entry_t *mmap) {

// }