#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk) {
    // zero out all fields of the struct
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;

    // intialize constant list too
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
    // first deallocate all of the memory
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);

    // also free the constants when we free the chunk
    freeValueArray(&chunk->constants);

    // reset the field of the chunk
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    // grow the array if it doesn't have capacity for the new byte
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;

        // set the new capacity
        chunk->capacity = GROW_CAPACITY(oldCapacity);

        // and grow the array of code & lines to new capacity
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    // store the new bytecode to the array
    chunk->code[chunk->count] = byte;

    // also store the line number to the line array
    chunk->lines[chunk->count] = line;

    // then increase the count
    chunk->count++;
}

int addConstant(Chunk *chunk, Value value)
{
    // add the value to the array of constants
    writeValueArray(&chunk->constants, value);

    // then return the index where the constant was appended
    return chunk->constants.count - 1;
}
