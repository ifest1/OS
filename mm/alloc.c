#include <stdlib.h>
#include <mm/mm.h>
#include <mm/alloc.h>

void _init_memory() {
    memory_start = (void *) usable_memory[1]->address;
    free_space = MAX_BLK_SIZE;
    free_lists[0] = (block *) memory_start;
    initialized = 1;
}

uint32_t _level_from_size(uint32_t size) {
    uint32_t level;
    for (level = MAX_LVLS; BLOCK_SIZE_AT_LVL(level) < size; level--);
    return level;
}

void _insert_freelist_head(block *blk, uint32_t level) {
    blk->next = free_lists[level];
    free_lists[level] = blk;
}

void *_pop_freelist_head(uint32_t level) {
    void *block;
    if (free_lists[level] != NULL) {
        block = free_lists[level];
        free_lists[level] = free_lists[level]->next;
    }
    return block;
}

void _delete_freelist_blk(void *blk, uint32_t level) {
    block *current = free_lists[level];

    if (current == blk) {
        free_lists[level] = free_lists[level]->next;
        return;
    }

    current = current->next;

    while (current) {
        if (current->next == blk)
            current->next = current->next->next;
        current = current->next;
    }
}

uint32_t _find_freelist_blk(void *buddy_addr, uint32_t level) {
    block *current;
    current = free_lists[level];
    while (current) {
        if ((void *)current == buddy_addr)
            return 1;
        current = current->next;
    }
    return NULL;
}

void * _find_freelist_blk_buddy(blk, size, index) {
    if (index & 1)
        return ((void *) (blk - size));
    return ((void *) (blk + size));
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

    for (level = _level_from_size(size); free_lists[level] == NULL; level--);

    for (;BLOCK_SIZE_AT_LVL(level) > size; level++) {
        void *buddy1 = (void *) free_lists[level];
        void *buddy2 = (block *) (buddy1 + BLOCK_SIZE_AT_LVL(level + 1));
        buddy1 = (block *) buddy1;

        _pop_freelist_head(level);
        _insert_freelist_head(buddy2, level + 1);
        _insert_freelist_head(buddy1, level + 1);
    }

    free_space -= size;

    return _pop_freelist_head(level);
}

void free_blk(void *blk, uint32_t size) {
    uint32_t level = _level_from_size(size);
    uint32_t index = INDEX_OF_POINTER_AT_LVL(memory_start, blk, level);

    while (level) {
        void *buddy_addr = _find_freelist_blk_buddy(blk, size, index);
        if (!(_find_freelist_blk(buddy_addr, level))) {
            _insert_freelist_head(blk, level);
            return;
        }
        _delete_freelist_blk(buddy_addr, level);
        size = BLOCK_SIZE_AT_LVL(level--);
    }
}