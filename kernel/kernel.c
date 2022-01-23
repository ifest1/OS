#include <stdlib.h>
#include <mm/mm.h>
#include <mm/page.h>
#include <mm/alloc.h>
#include <cpu/x86/init.h>

void main(mboot_info_t *mboot_info, uint32_t magic) {
    // void *blk1, *blk2, *blk3;
    x86_init();
    char buf[10];
    mmap_entry_t *entry = mboot_info->mmap_addr;

    for (int i = 0; i < mboot_info->mmap_length; i++) {
        entry = entry + 1;
        printk(itoa(entry->base_addr_high, 16, buf), 0);
        printk(itoa(entry->base_addr_low, 16, buf), 1);
    }
    // printk(itoa(magic, 16, buf), 1);
    // init_pgdir_entries();
    // init_first_pg_table();
    // set_usable_mm();
    // // print_mm_entries(usable_memory, 2);
    // blk1 = alloc(64);
    // itoa(blk1, 16, blk1);
    // printk(blk1, 1);

    // blk2 = alloc(64);
    // itoa(blk2, 16, blk2);
    // printk(blk2, 1);
    // free(blk2);

    // blk3 = alloc(64);
    // itoa(blk3, 16, blk3);
    // printk(blk3, 1);
}
