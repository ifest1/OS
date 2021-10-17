#include <stdint.h>
#ifndef PAGE_H__
#define PAGE_H__

#define PAGE_TABLES_BASE_LOC                    0x00100000
#define PAGE_DIR_ENTRY_SIZE                     1024
#define PAGE_ENTRY_SIZE                         1024
#define PAGES_TOTAL_SIZE                        4096

#define PRESENT                                 1
#define RW                                      2
#define US                                      4
#define PWT                                     8
#define PCD                                     16
#define ACCESSED                                32
#define PAGE_SIZE                               64
#define GLOBAL                                  128
#define PAT                                     256

typedef uint32_t                                pg_t;

pg_t *pgdir_table;;
pg_t *first_pg_table;

void init_pgdir_entries(void);
void init_first_pg_table(void);

#endif
