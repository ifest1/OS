#include <stdlib.h>
#include <mm/mm.h>
#include <mm/buddy_alloc.h>

void _init_memory() {
    memory_start = (void *) usable_memory[1]->address;
    deallocated = MAX_BLK_SIZE;
    free_lists[0] = (block *) memory_start;
}

uint32_t _level_from_size(uint32_t size) {
    uint32_t level;
    for (level = MAX_LVLS; BLOCK_SIZE_AT_LVL(level) < size; level--);
    return level;
}

void insert_head(block *blk, uint32_t level) {
    blk->next = free_lists[level];
    free_lists[level] = blk;
}

void delete_head(uint32_t level) {
    if (free_lists[level] != NULL)
        free_lists[level] = free_lists[level]->next;
}

void delete_free_block(void *blk, uint32_t level) {
    block *current;
    current = free_lists[level];

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

void *free_list_find(void *buddy_addr, uint32_t level) {
    block *current;
    current = free_lists[level];
    while (current) {
        if ((void *)current == buddy_addr)
            return current;
        current = current->next;
    }
    return NULL;
}

void *alloc(uint32_t size) {
    uint32_t level;
    block *blk;

    if (!initialized) {
        _init_memory();
        initialized = 1;
    }

    if (!deallocated) {
        printk("Not enough space.", 1);
        return NULL;
    }

    for (level = _level_from_size(size); free_lists[level] == NULL; level--);

    for (; BLOCK_SIZE_AT_LVL(level) > size; level++) {
        void *buddy1, *buddy2;

        buddy1 = (void *) free_lists[level];
        buddy2 = (block *) (buddy1 + BLOCK_SIZE_AT_LVL(level + 1));
        buddy1 = (block *) buddy1;

        delete_head(level);
        insert_head(buddy2, level + 1);
        insert_head(buddy1, level + 1);
    }

    blk = free_lists[level];

    delete_head(level);

    deallocated -= size;
    return blk;
}

void free_blk(void *blk, uint32_t size) {
    uint32_t level = _level_from_size(size);
    uint32_t index = INDEX_OF_POINTER_AT_LVL(memory_start, blk, level);

    void *buddy_addr;
    void *block_start;

    while (level >= 0) {
        if (index & 1) {
            buddy_addr = (void *) (blk - size);
            block_start = buddy_addr;
        }
        else {
            buddy_addr = (void *) (blk + size);
            block_start = blk;
        }

        if (buddy_addr == free_list_find(buddy_addr, level)) {
            delete_free_block(buddy_addr, level);
        }
        else {
            insert_head(blk, level);
            return;
        }
        level--;
        size = BLOCK_SIZE_AT_LVL(level);
    }
}