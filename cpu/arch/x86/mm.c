#include <cpu/x86/mm.h>
#include <stdlib.h>

int mm_comp(mmap_entry_t *mm1, mmap_entry_t *mm2) {
    return mm1->length < mm2->length;
}

void print_mmap(void) {
    char base_addr_l[20];
    char base_addr_h[20];
    char length[20];
    char type[20];
    mmap_entry_t *mm = (mmap_entry_t *) &MMAP_ENTRY;
    printk("| Address | Length | Type |", 1);
    for (uint8_t i = 0; i < MMAP_ENTRY_COUNT; i++) {
        mm = (mmap_entry_t *) &MMAP_ENTRY + i;
        uint32_t addr_l = (uint32_t) mm->address_l;
        uint32_t addr_h = (uint32_t) mm->address_h;
        itoa(addr_h, 16, base_addr_h);
        itoa(addr_l, 16, base_addr_l);
        itoa(mm->length, 16, length);
        itoa(mm->type, 16, type);
        printk(" ", 0);
        printk(base_addr_h, 0);
        printk(" ", 0);
        printk(base_addr_l, 0);
        printk(" ", 0);
        printk(length, 0);
        printk(" ", 0);
        printk(type, 1);
        printk(" ", 0);
    }
}

int get_avail_phys_mem() {
    int avail_mm;
    mmap_entry_t *mm = (mmap_entry_t *) &MMAP_ENTRY;
    for (uint8_t i = 0; i < MMAP_ENTRY_COUNT; i++) {
        mm = (mmap_entry_t *) &MMAP_ENTRY + i;
        if (mm->type == 1) avail_mm += mm->length; 
    }
    return avail_mm;
}

