#include <stdint.h>
#ifndef PAGE_H__
#define PAGE_H__
#define PAGE_DIR_ENTRY_SIZE                     1024
#define PAGE_ENTRY_SIZE                         1024
#define PAGES_TOTAL_SIZE                        4096

typedef uint32_t                                pg_t;

pg_t *pgdir_table;;
pg_t *first_pg_table;

void init_pgdir_entries(void);
void init_first_pg_table(void);

#endif
