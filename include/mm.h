#include "../include/stdint.h"

#define ARM      1
#define ARR      2

typedef struct {
    uint16_t base_addr_l;
    uint16_t base_addr_h;
    uint16_t length_l;
    uint16_t length_h;
    uint32_t type;
} __attribute__((packed)) mmap_entry_t;

// mmap_entry_t *mmap = (mmap_entry_t *) 0x1000;