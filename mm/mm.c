#include <mm/mm.h>
#include <stdlib.h>

// void print_mm_entries(mmap_entry_t **entries, uint8_t size) {
//     for (uint8_t i = 0; i < size; i++) {
//         char buf[10];
//         itoa(entries[i]->address, 16, buf);
//         printk(buf, 1);
//     }
// }

// void set_usable_mm() {
//     mmap_entry_t *mm = (mmap_entry_t *) &MMAP_ENTRY;
//     uint8_t k = 0;
//     for (uint8_t i = 0; i < MMAP_ENTRY_COUNT; i++) {
//         mm = (mmap_entry_t *) &MMAP_ENTRY + i;
//         if (mm->type == 1) {
//             available_mm += mm->length;
//             usable_memory[k] = mm;
//             k++;
//         }
//     }
// }

