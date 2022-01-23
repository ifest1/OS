#include <stdint.h>

#ifndef MM_H__
#define MM_H__

#define ARM                 1
#define ARR                 2


typedef struct {
    uint32_t                flags;
    uint32_t                mem_lower;
    uint32_t                mem_upper;
    uint32_t                boot_device;
    uint32_t                cmdline;
    uint32_t                mods_count;
    uint32_t                mods_addr;
    uint32_t                syms[4];
    uint32_t                mmap_length;
    uint32_t                mmap_addr;
    uint32_t                drives_length;
    uint32_t                drives_addr;
    uint32_t                config_table;
    uint32_t                boot_loader_name;
    uint32_t                apm_table;
    uint32_t                vbe_control_info;
    uint32_t                vbe_mode_info;
    uint16_t                vbe_mode;
    uint16_t                vbe_interface_seg;
    uint16_t                vbe_interface_off;
    uint16_t                vbe_interface_len;
    uint64_t                framebuffer_addr;
    uint32_t                framebuffer_pitch;
    uint32_t                framebuffer_width;
    uint32_t                framebuffer_height;
    uint8_t                 framebuffer_bpp;
    uint8_t                 framebuffer_type;
    uint8_t                 color_info[5];
} __attribute__((packed)) mboot_info_t;

typedef struct {
    uint32_t                size;
    uint32_t                base_addr_low;
    uint32_t                base_addr_high;
    uint32_t                length_low;
    uint32_t                length_high;
    uint32_t                type;
} __attribute__((packed)) mmap_entry_t;

mmap_entry_t *usable_memory[10];
int available_mm;

void set_usable_mm();
void print_mmap(void);
#endif
