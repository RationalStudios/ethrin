#include <calloc/calloc.h>

void *calloc(size_t m, size_t n)
{
    void *ptr;
    size_t *z;
    if(n && m > (size_t) - 1/n)
    {
        return 0;
    }

    n *= m;
    ptr = malloc(n);
    if(!ptr) return 0;
    if(((size_t *) ptr) [-1] & 7)
    {
        m = (n + sizeof (*z) - 1) / sizeof(*z);
        for(z=(size_t *)ptr; m; m--, z++) if(*z) *z=0;
    }
    return (void *) ptr;
}