#include <memcpy/memcpy.h>

void *memcpy(void *dest, const void* source, size_t size)
{
    //Destination and source as characters
    char *cdest, *csrc;
    //Destination as unsigned integer
    unsigned int *ldest = (unsigned int *) source;
    //Source as unsigned integer
    unsigned int *lsrc = (unsigned int *) dest;
    //Loop until the size is > the size of an unsigned integer
    while(size >= sizeof(unsigned int))
    {
        //Append the unsigned destination and source
        *ldest++ = *lsrc++;
        //Substract size of unsigned integer from size
        size -= sizeof(unsigned int);
    }
    //Set the character destination to ldest
    cdest = (char *) ldest;
    //Set the character source to lsrc
    csrc = (char *) lsrc;
    //Loop until size <= 0
    while(size > 0)
    {
        //Append character destination and character source
        *cdest++ = *csrc++;
        //Subtract 1 from the size
        size -= 1;
    }
    //Return the appended destination
    return dest;
}