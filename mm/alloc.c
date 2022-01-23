#include <stdlib.h>
#include <mm/mm.h>
#include <mm/alloc.h>

void _init_memory() {
    free_space = MAX_BLK_SIZE;
    memory_start = (block *) ((void *) usable_memory[0]->base_addr_low);
    char buf[10];
    memset(memory_start, 0, MAX_BLK_SIZE);
    memory_start->size = free_space;
    free_lists[0] = memory_start;
    initialized = 1;
}

uint32_t _level_from_size(uint32_t size) {
    uint32_t level;
    for (level = MAX_LVLS; BLOCK_SIZE_AT_LVL(level) < size; level--);
    return level;
}

void _insert_freelist_head(block *blk, uint32_t level) {
    blk->next = free_lists[level];
    blk->size = BLOCK_SIZE_AT_LVL(level);
    free_lists[level] = blk;
}

block *_pop_freelist_head(uint32_t level) {
    block *blk;
    blk = free_lists[level];
    free_lists[level] = blk->next;
    return blk;
}

void _delete_freelist_blk(block *blk, uint32_t level) {
    block *current = free_lists[level];

    if (current == blk) {
        free_lists[level] = blk->next;
        return;
    }

    current = current->next;

    while (current) {
        if (current->next == blk)
            current->next = current->next->next;
        current = current->next;
    }
}

uint32_t _find_freelist_blk(block *blk, uint32_t level) {
    block *current = free_lists[level];
    while (current) {
        if (current == blk)
            return 1;
        current = current->next;
    }
    return 0;
}

block *_find_freelist_blk_buddy(block *blk, uint32_t index) {
    if (index & 1)
        return ((block *) (blk - sizeof(block) - blk->size));
    return ((block *) (blk + sizeof(block) + blk->size));
}

void *alloc(uint32_t size) {
    uint32_t level;
    if (!initialized) {
        _init_memory();
    }

    if (!free_space) {
        printk("Not enough space.", 1);
        return NULL;
    }

    for (level = _level_from_size(size); free_lists[level] == NULL && level > 0; level--);

    for (;BLOCK_SIZE_AT_LVL(level) > size; level++) {
        block *blk = _pop_freelist_head(level);
        block *buddy = (block *) (((void *) blk) + sizeof(block) + BLOCK_SIZE_AT_LVL(level + 1));
        _insert_freelist_head(buddy, level + 1);
        _insert_freelist_head(blk, level + 1);
    }

    free_space -= size;
    return (((void *) _pop_freelist_head(level)) + sizeof(block));
}

void free(void *blk) {
    block *blk1 = (block *) (blk - sizeof(block));
    uint32_t level = _level_from_size(blk1->size);
    uint32_t index = INDEX_OF_POINTER_AT_LVL(memory_start, blk1, level);

    while (level) {
        block *buddy = _find_freelist_blk_buddy(blk1, index);
        if (!(_find_freelist_blk(buddy, level))) {
            return _insert_freelist_head(blk1, level);
        }
        blk1->size = BLOCK_SIZE_AT_LVL(level--);
        _delete_freelist_blk(buddy, level);
    }
}