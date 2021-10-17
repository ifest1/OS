#include <cpu/x86/page.h>

void init_pgdir_entries(void) {
    pgdir_table = (pg_t *) 0x00100000;
    for (uint16_t i = 0; i < PAGE_DIR_ENTRY_SIZE; i++) {
        pgdir_table[i] = 0x00000002;
    }
}

void init_first_pg_table(void) {
    first_pg_table = (pg_t *) (0x00100000 + (PAGES_TOTAL_SIZE));
    for (uint16_t i = 0; i < PAGE_ENTRY_SIZE; i++) {
        first_pg_table[i] = (i * 0x1000) | 3;
    }
}