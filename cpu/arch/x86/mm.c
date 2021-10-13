#include <cpu/x86/mm.h>
#include <stdlib.h>

int mm_comp(mmap_entry_t *mm1, mmap_entry_t *mm2) {
    return (mm1->length < mm2->length);
}

void print_mmap() {
    mmap_entry_t *mm = (mmap_entry_t *) &MMAP_ENTRY;

    ms(mm, 0, MMAP_ENTRY_COUNT - 1, mm_comp);

    for (uint8_t i = 0; i < MMAP_ENTRY_COUNT; i++) {
        printk(itoa(mm->length, 16, 10));
        printk("==============================");
        mm = mm + i;
    }
}