#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#define MAX_MEMORY_BLOCK_SIZE 20000
struct mem_block
{
    //Size allocated
    size_t size;
    //Free space left
    int free;
    //Next block
    struct mem_block *next;
};

//Initialization for a block of memory
void __malloc_initialize();
//Splits a block
void __malloc_split(struct mem_block *block, size_t size);
//Merges a block
void merge();
//Memory allocator
void *malloc(size_t size);
//For freeing a block
void free(void *ptr);
#endif