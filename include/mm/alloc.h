#include <stdint.h>

#define MAX_BLK_SIZE                                              1024
#define MIN_BLK_SIZE                                              16
#define MAX_LVLS                                                  5
#define BLOCKS_AT_LVL(n)                                          (1 << n)
#define BLOCK_SIZE_AT_LVL(n)                                      (MAX_BLK_SIZE / BLOCKS_AT_LVL(n))
#define INDEX_OF_POINTER_AT_LVL(memory_start, pointer, level)     (((int) pointer - (int) memory_start) / (BLOCK_SIZE_AT_LVL(level)))

struct entry {
    struct entry *next;
    uint32_t      size;
};
typedef struct entry block;

int free_space;
int initialized;
block *memory_start;
block *free_lists[MAX_LVLS];

/* API */
void *alloc(uint32_t size);
void free(void *blk);