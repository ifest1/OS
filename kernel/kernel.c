#include <stdlib.h>
#include <cpu/x86/mm.h>
#include <cpu/x86/init.h>
#include <cpu/x86/page.h>

void main() {
    x86_init();
    init_pgdir_entries();
    init_first_pg_table();
    print_mmap();
}
