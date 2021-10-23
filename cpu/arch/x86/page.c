#include <cpu/x86/page.h>

void init_pgdir_entries(void) {
    pgdir_table = (pg_t *) PAGE_TABLES_LOCATION;

    for (uint16_t i = 0; i < PAGE_DIR_NENTRIES; i++) {
        pgdir_table[i] = 0x00000002;
    }
}

void init_first_pg_table(void) {
    first_pg_table = (pg_t *) (PAGE_TABLES_LOCATION + (PAGE_DIR_NENTRIES * 4));

    for (uint16_t i = 0; i < PAGE_NENTRIES; i++) {
        first_pg_table[i] = (i * 0x1000) | PRESENT | RW;
    }
}
