#include <stdlib.h>
#include <mm/mm.h>
#include <mm/page.h>
#include <mm/alloc.h>
#include <cpu/x86/init.h>

void main(mboot_info_t *mboot_info, uint32_t magic) {
    void *blk1, *blk2, *blk3;
    x86_init();
    set_usable_mm(mboot_info->mmap_addr, mboot_info->mmap_length);
    // init_pgdir_entries();
    // init_first_pg_table();
    blk1 = alloc(64);
    printk(blk1, 1);

    // blk2 = alloc(64);
    // itoa(blk2, 16, blk2);
    // printk(blk2, 1);
    // free(blk2);

    // blk3 = alloc(64);
    // itoa(blk3, 16, blk3);
    // printk(blk3, 1);
}
