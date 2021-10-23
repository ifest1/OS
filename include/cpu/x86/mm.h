#include <stdint.h>

#ifndef MM_H__
#define MM_H__

#define ARM                 1
#define ARR                 2

typedef struct {
    uint32_t                address_l;
    uint32_t                address_h;
    uint64_t                length;
    uint64_t                type;
} __attribute__((packed)) mmap_entry_t;

extern uint8_t              MMAP_ENTRY_COUNT;
extern uint8_t              MMAP_ENTRY;

//extern uint32_t             AVAILABLE_PHYS_MEM;

int mm_comp(mmap_entry_t *mm1, mmap_entry_t *mm2);
int get_avail_phys_mem();
void print_mmap(void);
#endif
