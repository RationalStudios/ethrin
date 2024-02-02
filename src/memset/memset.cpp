#include <memset/memset.h>

void *memset(void *source, int count, size_t size)
{
    //We can use this to zero-fill pointers
    //Loop through the size
    for(int i = 0; i < size; i++)
        //Set item at i for source to the count
        ((char *) source)[i] = count;
    return source;
}