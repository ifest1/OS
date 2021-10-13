#include <mm.h>
#include <utils.h>
#include <print.h>

void print_mmap() {
    for (uint8_t i = 0; i < MMAP_ENTRY_COUNT; i++) {
        mmap_entry_t *mm_entry = (mmap_entry_t *) &MMAP_ENTRY + i;

        printk(itoa(mm_entry->base_addr, 16, 10));
        printk(itoa(mm_entry->length, 16, 10));
        printk(itoa(mm_entry->type, 16, 10));
        printk("==============================");
    }
}