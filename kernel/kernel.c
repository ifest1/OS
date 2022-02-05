#include <stdlib.h>
#include <mm/mm.h>
#include <mm/page.h>
#include <mm/alloc.h>
#include <cpu/x86/init.h>

void main(mboot_info_t *mboot_info, uint32_t magic) {
    void *blk1, *blk2, *blk3, *blk4;
    x86_init();
    set_usable_mm(mboot_info->mmap_addr, mboot_info->mmap_length);
    // init_pgdir_entries();
    // init_first_pg_table();

    blk1 = alloc(64);
    print("allocated memory at address: %d\n", blk1);
    free(blk1);

    blk2 = alloc(64);
    print("allocated memory at address: %d\n", blk2);
    free(blk2);

    blk3 = alloc(64);
    print("allocated memory at address: %d\n", blk3);
    free(blk3);

    blk4 = alloc(64);
    print("allocated memory at address: %d\n", blk4);
    free(blk4);
}
