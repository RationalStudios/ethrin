#include <sys/portio.h>

inline uint8_t inb(uint16_t port)
{
    //The value to be returned
    uint8_t value;
    //Read data from port into the value
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    //Return read value
    return value;
}

inline uint16_t inw(uint16_t port)
{
    //The value to be read
    uint16_t value;
    //Read data from port
    asm volatile("inw %1, %0" : "=a"(value) : "Nd"(port));
    //Return the value
    return value;
}

inline uint32_t inl(uint16_t port)
{
    //The value to be read
    uint32_t value;
    //Read data into the value
    asm volatile("inl %1, %0" : "=a"(value) : "Nd"(port));
    //Return the value
    return value;
}

inline void outb(uint16_t port, uint8_t value)
{
    //Toss the data and port in, write the data to the port
    asm volatile("outb %0, %1" :: "a"(value), "dN"(port));
}

inline void outw(uint16_t port, uint16_t value)
{
    //Toss the data in, write it to the port
    asm volatile("outw %0, %1" :: "a"(value), "dN"(port));
}

inline void outl(uint16_t port, uint32_t value)
{
    //Toss the data to the port
    asm volatile("outl %0, %1" :: "a"(value), "dN"(port));
}

inline void outsw(uint16_t port, uint8_t* value)
{
    //Send the data to the port
    asm volatile("rep outsw");
}