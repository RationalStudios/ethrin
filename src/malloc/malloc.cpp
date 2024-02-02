#include <malloc/malloc.h>
//Max memory, self explanatory
char max_mem[MAX_MEMORY_BLOCK_SIZE];
//Our free list
struct mem_block *free_list = (struct mem_block*) max_mem;
//Page count
int page_count = 0;
//Page
struct mem_block block_page[MAX_MEMORY_BLOCK_SIZE];
//Memory stuff
char memory[MAX_MEMORY_BLOCK_SIZE];

//Initialization for a block of memory
void __malloc_initialize()
{
    //Set size of block pages
    free_list->size = MAX_MEMORY_BLOCK_SIZE - sizeof(struct mem_block);
    //Set free to 1
    free_list->free = 1;
    //Empty out the next block
    free_list->next = NULL;
}

//Splits a block
void __malloc_split(struct mem_block *block, size_t size)
{
    //Create a new block
    struct mem_block *new_block = (struct mem_block *)((char *) block + size + sizeof(struct mem_block));
    //Set the size
    new_block->size = (block->size) - size + sizeof(struct mem_block);
    //Set free to 1
    new_block->free = 1;
    //Set the next block
    new_block->next = block->next;
    //Set the block size
    block->size = size;
    //Set block free to 0
    block->free = 0;
    //Set the next block for block to be new block
    block->next = new_block;
}

//Merges a block
void merge()
{
    //Current and previous memory block
    struct mem_block *current, *previous;
    //Set current block to free list
    current = free_list;
    //Loop until the next block is null
    while((current->next) != NULL)
    {
        //Check if current and next block is free
        if((current->free) && (current->next->free))
        {
            //Update the size of current block
            current->size += (current->next->size) + sizeof(struct mem_block);
            //Set the next block to next block's next block
            current->next = current->next->next;
        }
        //Set the previous block to the current block
        previous = current;
        //Move to the next block
        current = current->next;
    }
}

//Memory allocator
void *malloc(size_t size)
{
    //Create a current and previous block
    struct mem_block *current, *previous;
    //The beautiful result :')
    void *result;
    //Check if the memory has not been initialized. If so, initialize the memory
    if(!(free_list->size)) __malloc_initialize();
    //Set the current block to free list
    current = free_list;
    //Make the temporary current pointer point to the start of our block list
    while((((current->size) < size) || ((current->free) == 0)) && (current->next !=  NULL))
    {
        //Set the previous block to current block
        previous = current;
        //Set current block to next
        current = current->next;
    }
    //Check if the size of the current block matches given size
    if(current->size == size)
    {
        //Set free to 0
        current->free = 0;
        //Set the result
        result = (void *) ++current;
        //Return the end result
        return result;
    }
    else if(current->size > (size + sizeof(struct mem_block)))
    {
        //Split the current block
        __malloc_split(current, size);
        //Set the result
        result = (void *) ++current;
        //Return the result
        return result;
    }

    //Something happened, still return null
    return NULL;
}

//For freeing a block
void free(void *ptr)
{
    //Check if a pointer's address resides between memory range
    if(((void *) memory <= ptr) && (ptr <= (void *)(memory + MAX_MEMORY_BLOCK_SIZE)))
    {
        //Create a current block
        struct mem_block *current = (struct mem_block*) ptr;
        //Remove one from the current block
        --current;
        //Free it up
        current->free = 1;
        //Merge
        merge();
    }
}