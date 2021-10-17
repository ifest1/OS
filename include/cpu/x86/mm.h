#include <stdint.h>

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

int mm_comp(mmap_entry_t *mm1, mmap_entry_t *mm2);
void print_mmap(void);
#endif