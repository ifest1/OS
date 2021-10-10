#include "stdint.h"
#ifndef MM_H__
#define MM_H__
#define MMAP_ENTRY_COUNT    0x5000
#define MMAP_ENTRY          0x5004
#define ARM                 1
#define ARR                 2

typedef struct {
    uint32_t base_addr_l;
    uint32_t base_addr_h;
    uint32_t length_l;
    uint32_t length_h;
    uint32_t type;
    uint32_t acpi;
} __attribute__((packed)) mmap_entry_t;

#endif