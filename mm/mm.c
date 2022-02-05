#include <mm/mm.h>
#include <stdlib.h>


void print_mm_entries(mmap_entry_t *entry, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        if (entry->type == 0) break;
        print("Type: %d\n", entry->type);
        print("Address: %d %d\n", entry->base_addr_high, entry->base_addr_low);
        entry++;
    }
}

void set_usable_mm(mmap_entry_t *entry, uint32_t size) {
    uint32_t i = 0;
    while (i < size && entry->type != 0) {
        if (entry->type == 1) {
            usable_memory[i] = entry;
            print("Type: %d\n", entry->type);
            print("Address: %d %d\n", entry->base_addr_high, entry->base_addr_low);
            i++;
        }
        entry++;
    }
}

