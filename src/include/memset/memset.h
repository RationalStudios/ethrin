#ifndef MEMSET_H
#define MEMSET_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *source, int count, size_t size);

#ifdef __cplusplus
}
#endif
#endif