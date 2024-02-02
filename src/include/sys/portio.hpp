#ifndef PORT_IO_HPP
#define PORT_IO_HPP
#include <stdint.h>
extern "C" inline uint8_t inb(uint16_t port);
extern "C" inline uint16_t inw(uint16_t port);
extern "C" inline uint32_t inl(uint16_t port);

extern "C" inline void outb(uint16_t port, uint8_t value);
extern "C" inline void outw(uint16_t port, uint16_t value);
extern "C" inline void outl(uint16_t port, uint32_t value);
extern "C" inline void outsw(uint16_t port, uint8_t* value);
#endif