#ifndef MEMCPY_H
#define MEMCPY_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void *dest, const void* source, size_t size);

#ifdef __cplusplus
}
#endif
#endif