#include <stdlib.h>
#include <file.h>
#include <mm/mm.h>
#include <mm/page.h>
#include <mm/alloc.h>
#include <cpu/x86/init.h>


void main(mboot_info_t *mboot_info, uint32_t magic) {
    char buf[10] = {'a', 'b', 'c', '\0'};
    x86_init();
    print("magic_number: %d\n", magic);
    set_usable_mm(mboot_info->mmap_addr, mboot_info->mmap_length);
    // init_pgdir_entries();
    // init_first_pg_table();
    write(1, buf, 30);
}
