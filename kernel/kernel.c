#include <stdlib.h>
#include <mm/mm.h>
#include <mm/page.h>
#include <mm/buddy_alloc.h>
#include <cpu/x86/init.h>

void main() {
    void *blk1, *blk2, *blk3;

    x86_init();
    init_pgdir_entries();
    init_first_pg_table();
    set_usable_mm();
    // print_mm_entries(usable_memory, 2);
    blk1 = alloc(64);
    itoa(blk1, 16, blk1);
    printk(blk1, 1);

    blk2 = alloc(64);
    itoa(blk2, 16, blk2);
    printk(blk2, 1);
    free_blk(blk2, 64);

    blk3 = alloc(64);
    itoa(blk3, 16, blk3);
    printk(blk3, 1);
}
