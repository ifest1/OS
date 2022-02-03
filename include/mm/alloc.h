#include <stdint.h>

#define MAX_BLK_SIZE                1024
#define MIN_BLK_SIZE                16
#define MAX_LVLS                    5
#define BLK_STRUCT_SIZE             sizeof(block)

struct entry {
    struct entry *next;
    uint32_t      size;
    uint8_t       level;
};
typedef struct entry block;

uint64_t mm_available;
uint64_t initialized;

uint32_t _level_from_size(uint32_t size);
uint32_t _blocks_at_level(uint32_t level);
uint32_t _block_size_at_level(uint32_t level);

block *memory_start;
block *free_lists[MAX_LVLS];
uint32_t block_sizes[MAX_LVLS];

/* API */
void *alloc(uint32_t size);
void free(void *blk);