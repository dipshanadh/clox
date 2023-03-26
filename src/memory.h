#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// macro to calculate the new capacity based on the current capacity
#define GROW_CAPACITY(capacity) \
    (capacity < 8 ? 8 : capacity * 2)

// macro to create or grow the array to the new count
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type *)reallocate(pointer, sizeof(type) * oldCount, sizeof(type) * newCount)

// macro to free the array by passing in 0 for new size
#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * oldCount, 0)

// function for allocating memory, freeing it and changing the size of exisiting allocation
void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif