#ifndef STDIO_H
#define STDIO_H
#include <stdint.h>
struct stdio_buffer
{
    int pos;
    void *content;
    struct stdio_buffer *next;
    struct stdio_buffer *prev;
};

void add_to_buffer(void *item);
//Convert hex to string
void htoc(uint16_t hex);
int8_t is_digit(char c);
int8_t is_alpha(char c);
int8_t is_alpha_num(char c);
void itoa(unsigned i, unsigned base, char *buffer);
int32_t atoi(const char *text);
void printf(char *fmt, ...);

extern "C" int count;
#endif