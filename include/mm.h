#include "stdint.h"
#ifndef MM_H__
#define MM_H__
#define ARM                 1
#define ARR                 2

typedef struct {
    uint64_t                base_addr;
    uint64_t                length;
    uint64_t                type;
} __attribute__((packed)) mmap_entry_t;

extern uint8_t MMAP_ENTRY_COUNT;
extern uint8_t MMAP_ENTRY;

void print_mmap(mmap_entry_t *mmap);
mmap_entry_t *order_mmap(mmap_entry_t *mmap);
#endif