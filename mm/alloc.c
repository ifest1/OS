#include <stdlib.h>
#include <mm/mm.h>
#include <mm/alloc.h>

void _init_memory() {
    mm_available = MAX_BLK_SIZE;
    memory_start = (block *) ((void *) usable_memory[0]->base_addr_low + 1);
    memory_start->size = mm_available;
    memory_start->level = 0;
    free_lists[0] = (block *) memory_start;

    for (uint32_t level = 0; level < MAX_LVLS; level++) {
        block_sizes[level] = (MAX_BLK_SIZE / (1 << level));
    }

    initialized = 1;
}

uint32_t _level_from_size(uint32_t size) {
    uint32_t level;
    for (level = MAX_LVLS; block_sizes[level] < size; level--);
    return level;
}


void _insert_freelist_head(block *blk, uint32_t level) {
    uint32_t size = block_sizes[level];
    blk->next = free_lists[level];
    blk->size = size;
    blk->level = level;
    free_lists[level] = blk;
}


block *_pop_freelist_head(uint32_t level) {
    block *blk;
    blk = free_lists[level];
    free_lists[level] = free_lists[level]->next;
    return blk;
}


void _delete_freelist_blk(block *blk, uint32_t level) {
    block *current = free_lists[level];

    if (current == blk) {
        free_lists[level] = free_lists[level]->next;
        return;
    }

    while (current != NULL && current->next != blk) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    current->next = current->next->next;
}


block *_find_freelist_blk(block *blk, uint32_t level) {
    block *current = free_lists[level];

    while (current != NULL && current != blk) {
        current = current->next;
    }

    return current;
}


void *_get_blk_buddy(block *blk) {
    block *buddy = ((block *) (((void *) blk) - BLK_STRUCT_SIZE - blk->size));
    uint32_t level = _level_from_size(blk->size);
    buddy = _find_freelist_blk(buddy, level);

    if (buddy) {
        return buddy;
    }

    buddy = ((block *) (((void *) blk) + BLK_STRUCT_SIZE + blk->size));
    return _find_freelist_blk(buddy, level);
}


void *alloc(uint32_t size) {
    uint32_t level;
    block *blk;

    if (!initialized) {
        _init_memory();
    }

    if (mm_available < size) {
        return NULL;
    }

    for (level = _level_from_size(size); free_lists[level] == NULL; level--);

    for (; block_sizes[level] > size; level++) {
        block *blk = _pop_freelist_head(level);
        uint32_t next_lvl_size = block_sizes[(level + 1)];
        block *buddy = (block *) (((void *) blk) + BLK_STRUCT_SIZE + next_lvl_size);
        _insert_freelist_head(buddy, level + 1);
        _insert_freelist_head(blk, level + 1);
    }

    mm_available -= (size + BLK_STRUCT_SIZE);
    return (((void *) _pop_freelist_head(level)) + BLK_STRUCT_SIZE);
}

void free(void *chunk) {
    block *blk = (block *) (chunk - BLK_STRUCT_SIZE);
    uint32_t level = _level_from_size(blk->size);

    mm_available += (blk->size + BLK_STRUCT_SIZE);

    while (level >= 0) {
        block *buddy = _get_blk_buddy(blk);
        if (!(buddy)) {
            return _insert_freelist_head(blk, level);
        }
        _delete_freelist_blk(buddy, level);
        blk->size = block_sizes[--level];
    }
}